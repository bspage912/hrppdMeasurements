#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <dirent.h>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"

int main(int argc, char* argv[])
{
  if(argc != 3) {
    printf("Usage: %s <input-csv-file-directory> <output-root-file-name>\n", argv[0]);
    exit(-1);
  } //if

  DIR *curr_dir = opendir(argv[1]);
  struct dirent *curr_file;
  assert(curr_dir);

  std::vector<std::vector<double>*> branches; 
  
  // Create a new ROOT file and tree
  auto *rootFile = new TFile(argv[2], "RECREATE");
  auto *tree = new TTree("tree", "Data from CSV");

  //std::vector<std::string> header;

  unsigned int number_of_files = 0;
  bool reference_header_exists = false;
  
  while((curr_file = readdir(curr_dir))) {
    if (!strcmp(curr_file->d_name, ".") || !strcmp(curr_file->d_name, "..")) continue;
    {
      unsigned len = strlen(curr_file->d_name);
      if (len < 4 || strcmp(curr_file->d_name + len - 4, ".csv")) continue;
    }
    
    // Open the CSV file
    auto inputFileName = std::string(argv[1]) + "/" + curr_file->d_name;
    std::ifstream file(inputFileName);
    if (!file.is_open()) {
      std::cerr << "Error opening file!" << std::endl;
      exit(-2);
    } //if
    
    std::cout << "Processing File: " << inputFileName << std::endl;

    number_of_files++;
    
    // Read the header lines first;
    {
      std::string line;
      bool time_line_found = false;
      unsigned line_counter = 0;
	
      while (std::getline(file, line)) {
	if(line.size() == 0) continue;
	//+std::cout << "Skipping Line: " << line << std::endl;
	
	// Remove CR, otherwise tree->Branch() gets confused;
	if(line[line.size()-1] == 13) line[line.size()-1] = 0;
	
	if(reference_header_exists)
	  {
	    if (!memcmp(line.c_str(), "TIME", 4)) time_line_found = true;
	  }
	else
	  {
	    TString name; name.Form("header%02d", line_counter);
	    rootFile->WriteObject(&line, name.Data());
	    
	    // Yes, before the string (line 17 in particular) was modified;
	    //header.push_back(line);
	    
	    // FIXME: do it better if ever have issues with a variable length header;
	    if(!memcmp(line.c_str(), "TIME", 4))
	      {
		time_line_found = true;
		
		// Avoid using strtok(); do head counting by hand;
		static std::vector<const char*> tokens;
		tokens.push_back(line.c_str());
		for(unsigned iq=0; iq<line.length(); iq++)
		  {
		    if(line[iq] == ',')
		      {
			line[iq] = 0;
			tokens.push_back(&line[iq+1]);
		      } //for iq..if
		  }
		    
		for(auto &token: tokens)
		  {
		    branches.push_back(new std::vector<double>());
		    tree->Branch(token, branches[branches.size()-1]);
		  } //for token
		
		break;
	      } //if
	  } //else

	if(time_line_found) std::cout << "Header Length = " << line_counter << std::endl;
	if(time_line_found) break;
	line_counter++;
      } //while

      if (!time_line_found) {
	printf("\n\n @@@ File %s has no line starting with 'TIME'! Skipping.\n\n",
	       inputFileName.c_str());
	//exit(-1);
	goto _next_file;
      } //if
      
      // After the very first file was imported;
      reference_header_exists = true;
    }

    // Reset the branch buffers;
    for(auto &branch: branches)
      branch->clear();
      
    // Read the rest of the file line by line;
    {
      const unsigned dim = branches.size();
      std::string line, value;
      unsigned int record_length = 0;
      
      while (std::getline(file, line)) {
	if (line.size() == 0) continue;

	std::stringstream ss(line);
	unsigned entry_counter = 0;
	
	while ((ss.rdstate() & std::ios_base::eofbit) == 0) {
	  std::getline(ss, value, ',');
	  branches[entry_counter++]->push_back(std::stod(value));
	} //while

	record_length++;
	
	assert(entry_counter == dim);
      } //while

      std::cout << "Record Length = " << record_length << std::endl;
    }
      
    // Close the CSV file
    file.close();
    
    tree->Fill();

  _next_file:
    continue;
  } //while
  
  // Write the tree to the ROOT file
  tree->Write();
  rootFile->Close();
  
  // Clean up
  delete rootFile;

  std::cout << "Processed Files: " << number_of_files << std::endl;
  std::cout << "Data successfully written to " << argv[2] << std::endl;
  
  exit(0);//return 0;
} // main()
