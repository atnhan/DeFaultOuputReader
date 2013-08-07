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
  if (argc != 7) {
    std::cout<<"Usage: input-path input-file output-path output-file domain problem"<<std::endl;
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
  std::string line;
  std::ifstream infile(ifname);
  
  // If there is no output file from DeFault, exit
  if (!infile.is_open())
    return 0;

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
  // Close the input file
  infile.close();
 
  if (!sols.empty()) {
    // Write to the output file in csv format
    std::string ofname(argv[3]);
    if (ofname.at(ofname.length()-1)!='/')
      ofname += "/";
    ofname += argv[4]; 
    std::ofstream outfile(ofname);
  
    // Comments
    outfile<<"# DeFault:  java -jar default-1.0.0.jar testfiles/incomplete/garland.pddl testfiles/incomplete/garlandprob1.pddl dan.out  pode2 anytime strict 5"<<std::endl;
    // Headers
    outfile<<"domain,problem,plan_id,plan_length,plan_robustness,total_time"<<std::endl;
    std::string domain(argv[5]);
    std::string problem(argv[6]);
    // Solution plan, each on a line. Attributes not available are -1
    for (size_t i=0; i<sols.size(); i++) {
      outfile<<domain<<","<<problem<<","<<i+1<<","<<sols[i].length<<","<<1.0-sols[i].fail_prob<<","<<sols[i].time;
      if (i < sols.size()-1) outfile<<std::endl;
    }
    // Close the output file
    outfile.close();
  }
  return 0;
}
