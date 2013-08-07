#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

struct SOL {
  double time;
  size_t length;
  double fail_prob;
};

int main(int argc, char* argv[]) {
  if (argc != 5) {
    std::cout<<"Usage: input-path input-file output-path output-file"<<std::endl;
    exit(1);
  }
  std::string ifname(argv[1]);
  if (ifname.at(ifname.length()-1)!='/')
    ifname += "/";
  ifname += argv[2];
  
  std::string sol_str("time\tnodes\tlen\tfail pr\teval time\t");
  std::string inc_str("Incomplete Features:");
  std::string time_str("Total Time (s):");

  std::vector<SOL> sols;
  double total_time = 0;

  std::string line;
  std::ifstream infile(ifname);

  while (std::getline(infile, line)) {
    if (line.compare(sol_str)==0) {      
      // Start to read solutions line by line until the next incomplete features string
      while (std::getline(infile, line) && line.find(inc_str) == std::string::npos) {
	  std::stringstream ss(line);
	  double time; size_t nodes, len; double fail_prob, eval_time;
	  ss >> time >> nodes >> len >> fail_prob >> eval_time;
	  SOL sol;
	  sol.time = time; sol.length = len; sol.fail_prob = fail_prob;
	  sols.push_back(sol);
      }
    }
    else {
      if (line.find(time_str) != std::string::npos) {
	total_time = atof(line.substr(time_str.length()).c_str());
	std::cout<<"Total time: "<<total_time<<std::endl;
      }
    }
  }
  // Close the input file
  std::string ofname(argv[3]);
  if (ofname.at(ofname.length()-1)!='/')
    ofname += "/";
  ofname += argv[4];  

  // Write to the output file
  std::ofstream outfile(ofname);
  
}
