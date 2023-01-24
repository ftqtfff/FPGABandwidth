#include <systemc>
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <stdint.h>
#include "SysCFileHandler.h"
#include "ap_int.h"
#include "ap_fixed.h"
#include <complex>
#include <stdbool.h>
#include "autopilot_cbe.h"
#include "hls_stream.h"
#include "hls_half.h"
#include "hls_signal_handler.h"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

// wrapc file define:
#define AUTOTB_TVIN_dataIn_V_data_V "../tv/cdatafile/c.ethernet_header_inserter.autotvin_dataIn_V_data_V.dat"
#define AUTOTB_TVOUT_dataIn_V_data_V "../tv/cdatafile/c.ethernet_header_inserter.autotvout_dataIn_V_data_V.dat"
#define AUTOTB_TVIN_dataIn_V_keep_V "../tv/cdatafile/c.ethernet_header_inserter.autotvin_dataIn_V_keep_V.dat"
#define AUTOTB_TVOUT_dataIn_V_keep_V "../tv/cdatafile/c.ethernet_header_inserter.autotvout_dataIn_V_keep_V.dat"
#define AUTOTB_TVIN_dataIn_V_strb_V "../tv/cdatafile/c.ethernet_header_inserter.autotvin_dataIn_V_strb_V.dat"
#define AUTOTB_TVOUT_dataIn_V_strb_V "../tv/cdatafile/c.ethernet_header_inserter.autotvout_dataIn_V_strb_V.dat"
#define AUTOTB_TVIN_dataIn_V_last_V "../tv/cdatafile/c.ethernet_header_inserter.autotvin_dataIn_V_last_V.dat"
#define AUTOTB_TVOUT_dataIn_V_last_V "../tv/cdatafile/c.ethernet_header_inserter.autotvout_dataIn_V_last_V.dat"
#define WRAPC_STREAM_SIZE_IN_dataIn_V_data_V "../tv/stream_size/stream_size_in_dataIn_V_data_V.dat"
#define WRAPC_STREAM_INGRESS_STATUS_dataIn_V_data_V "../tv/stream_size/stream_ingress_status_dataIn_V_data_V.dat"
#define WRAPC_STREAM_SIZE_IN_dataIn_V_keep_V "../tv/stream_size/stream_size_in_dataIn_V_keep_V.dat"
#define WRAPC_STREAM_INGRESS_STATUS_dataIn_V_keep_V "../tv/stream_size/stream_ingress_status_dataIn_V_keep_V.dat"
#define WRAPC_STREAM_SIZE_IN_dataIn_V_strb_V "../tv/stream_size/stream_size_in_dataIn_V_strb_V.dat"
#define WRAPC_STREAM_INGRESS_STATUS_dataIn_V_strb_V "../tv/stream_size/stream_ingress_status_dataIn_V_strb_V.dat"
#define WRAPC_STREAM_SIZE_IN_dataIn_V_last_V "../tv/stream_size/stream_size_in_dataIn_V_last_V.dat"
#define WRAPC_STREAM_INGRESS_STATUS_dataIn_V_last_V "../tv/stream_size/stream_ingress_status_dataIn_V_last_V.dat"
// wrapc file define:
#define AUTOTB_TVIN_dataOut_V_data_V "../tv/cdatafile/c.ethernet_header_inserter.autotvin_dataOut_V_data_V.dat"
#define AUTOTB_TVOUT_dataOut_V_data_V "../tv/cdatafile/c.ethernet_header_inserter.autotvout_dataOut_V_data_V.dat"
#define AUTOTB_TVIN_dataOut_V_keep_V "../tv/cdatafile/c.ethernet_header_inserter.autotvin_dataOut_V_keep_V.dat"
#define AUTOTB_TVOUT_dataOut_V_keep_V "../tv/cdatafile/c.ethernet_header_inserter.autotvout_dataOut_V_keep_V.dat"
#define AUTOTB_TVIN_dataOut_V_strb_V "../tv/cdatafile/c.ethernet_header_inserter.autotvin_dataOut_V_strb_V.dat"
#define AUTOTB_TVOUT_dataOut_V_strb_V "../tv/cdatafile/c.ethernet_header_inserter.autotvout_dataOut_V_strb_V.dat"
#define AUTOTB_TVIN_dataOut_V_last_V "../tv/cdatafile/c.ethernet_header_inserter.autotvin_dataOut_V_last_V.dat"
#define AUTOTB_TVOUT_dataOut_V_last_V "../tv/cdatafile/c.ethernet_header_inserter.autotvout_dataOut_V_last_V.dat"
#define WRAPC_STREAM_SIZE_OUT_dataOut_V_data_V "../tv/stream_size/stream_size_out_dataOut_V_data_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_dataOut_V_data_V "../tv/stream_size/stream_egress_status_dataOut_V_data_V.dat"
#define WRAPC_STREAM_SIZE_OUT_dataOut_V_keep_V "../tv/stream_size/stream_size_out_dataOut_V_keep_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_dataOut_V_keep_V "../tv/stream_size/stream_egress_status_dataOut_V_keep_V.dat"
#define WRAPC_STREAM_SIZE_OUT_dataOut_V_strb_V "../tv/stream_size/stream_size_out_dataOut_V_strb_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_dataOut_V_strb_V "../tv/stream_size/stream_egress_status_dataOut_V_strb_V.dat"
#define WRAPC_STREAM_SIZE_OUT_dataOut_V_last_V "../tv/stream_size/stream_size_out_dataOut_V_last_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_dataOut_V_last_V "../tv/stream_size/stream_egress_status_dataOut_V_last_V.dat"
// wrapc file define:
#define AUTOTB_TVIN_arpTableReplay_V "../tv/cdatafile/c.ethernet_header_inserter.autotvin_arpTableReplay_V.dat"
#define AUTOTB_TVOUT_arpTableReplay_V "../tv/cdatafile/c.ethernet_header_inserter.autotvout_arpTableReplay_V.dat"
#define WRAPC_STREAM_SIZE_IN_arpTableReplay_V "../tv/stream_size/stream_size_in_arpTableReplay_V.dat"
#define WRAPC_STREAM_INGRESS_STATUS_arpTableReplay_V "../tv/stream_size/stream_ingress_status_arpTableReplay_V.dat"
// wrapc file define:
#define AUTOTB_TVIN_arpTableRequest_V "../tv/cdatafile/c.ethernet_header_inserter.autotvin_arpTableRequest_V.dat"
#define AUTOTB_TVOUT_arpTableRequest_V "../tv/cdatafile/c.ethernet_header_inserter.autotvout_arpTableRequest_V.dat"
#define WRAPC_STREAM_SIZE_OUT_arpTableRequest_V "../tv/stream_size/stream_size_out_arpTableRequest_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_arpTableRequest_V "../tv/stream_size/stream_egress_status_arpTableRequest_V.dat"
// wrapc file define:
#define AUTOTB_TVIN_myMacAddress "../tv/cdatafile/c.ethernet_header_inserter.autotvin_myMacAddress.dat"
#define AUTOTB_TVOUT_myMacAddress "../tv/cdatafile/c.ethernet_header_inserter.autotvout_myMacAddress.dat"
// wrapc file define:
#define AUTOTB_TVIN_regSubNetMask "../tv/cdatafile/c.ethernet_header_inserter.autotvin_regSubNetMask.dat"
#define AUTOTB_TVOUT_regSubNetMask "../tv/cdatafile/c.ethernet_header_inserter.autotvout_regSubNetMask.dat"
// wrapc file define:
#define AUTOTB_TVIN_regDefaultGateway "../tv/cdatafile/c.ethernet_header_inserter.autotvin_regDefaultGateway.dat"
#define AUTOTB_TVOUT_regDefaultGateway "../tv/cdatafile/c.ethernet_header_inserter.autotvout_regDefaultGateway.dat"

#define INTER_TCL "../tv/cdatafile/ref.tcl"

// tvout file define:
#define AUTOTB_TVOUT_PC_dataIn_V_data_V "../tv/rtldatafile/rtl.ethernet_header_inserter.autotvout_dataIn_V_data_V.dat"
#define AUTOTB_TVOUT_PC_dataIn_V_keep_V "../tv/rtldatafile/rtl.ethernet_header_inserter.autotvout_dataIn_V_keep_V.dat"
#define AUTOTB_TVOUT_PC_dataIn_V_strb_V "../tv/rtldatafile/rtl.ethernet_header_inserter.autotvout_dataIn_V_strb_V.dat"
#define AUTOTB_TVOUT_PC_dataIn_V_last_V "../tv/rtldatafile/rtl.ethernet_header_inserter.autotvout_dataIn_V_last_V.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_dataOut_V_data_V "../tv/rtldatafile/rtl.ethernet_header_inserter.autotvout_dataOut_V_data_V.dat"
#define AUTOTB_TVOUT_PC_dataOut_V_keep_V "../tv/rtldatafile/rtl.ethernet_header_inserter.autotvout_dataOut_V_keep_V.dat"
#define AUTOTB_TVOUT_PC_dataOut_V_strb_V "../tv/rtldatafile/rtl.ethernet_header_inserter.autotvout_dataOut_V_strb_V.dat"
#define AUTOTB_TVOUT_PC_dataOut_V_last_V "../tv/rtldatafile/rtl.ethernet_header_inserter.autotvout_dataOut_V_last_V.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_arpTableReplay_V "../tv/rtldatafile/rtl.ethernet_header_inserter.autotvout_arpTableReplay_V.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_arpTableRequest_V "../tv/rtldatafile/rtl.ethernet_header_inserter.autotvout_arpTableRequest_V.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_myMacAddress "../tv/rtldatafile/rtl.ethernet_header_inserter.autotvout_myMacAddress.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_regSubNetMask "../tv/rtldatafile/rtl.ethernet_header_inserter.autotvout_regSubNetMask.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_regDefaultGateway "../tv/rtldatafile/rtl.ethernet_header_inserter.autotvout_regDefaultGateway.dat"

class INTER_TCL_FILE {
  public:
INTER_TCL_FILE(const char* name) {
  mName = name; 
  dataIn_V_data_V_depth = 0;
  dataIn_V_keep_V_depth = 0;
  dataIn_V_strb_V_depth = 0;
  dataIn_V_last_V_depth = 0;
  dataOut_V_data_V_depth = 0;
  dataOut_V_keep_V_depth = 0;
  dataOut_V_strb_V_depth = 0;
  dataOut_V_last_V_depth = 0;
  arpTableReplay_V_depth = 0;
  arpTableRequest_V_depth = 0;
  myMacAddress_depth = 0;
  regSubNetMask_depth = 0;
  regDefaultGateway_depth = 0;
  trans_num =0;
}
~INTER_TCL_FILE() {
  mFile.open(mName);
  if (!mFile.good()) {
    cout << "Failed to open file ref.tcl" << endl;
    exit (1); 
  }
  string total_list = get_depth_list();
  mFile << "set depth_list {\n";
  mFile << total_list;
  mFile << "}\n";
  mFile << "set trans_num "<<trans_num<<endl;
  mFile.close();
}
string get_depth_list () {
  stringstream total_list;
  total_list << "{dataIn_V_data_V " << dataIn_V_data_V_depth << "}\n";
  total_list << "{dataIn_V_keep_V " << dataIn_V_keep_V_depth << "}\n";
  total_list << "{dataIn_V_strb_V " << dataIn_V_strb_V_depth << "}\n";
  total_list << "{dataIn_V_last_V " << dataIn_V_last_V_depth << "}\n";
  total_list << "{dataOut_V_data_V " << dataOut_V_data_V_depth << "}\n";
  total_list << "{dataOut_V_keep_V " << dataOut_V_keep_V_depth << "}\n";
  total_list << "{dataOut_V_strb_V " << dataOut_V_strb_V_depth << "}\n";
  total_list << "{dataOut_V_last_V " << dataOut_V_last_V_depth << "}\n";
  total_list << "{arpTableReplay_V " << arpTableReplay_V_depth << "}\n";
  total_list << "{arpTableRequest_V " << arpTableRequest_V_depth << "}\n";
  total_list << "{myMacAddress " << myMacAddress_depth << "}\n";
  total_list << "{regSubNetMask " << regSubNetMask_depth << "}\n";
  total_list << "{regDefaultGateway " << regDefaultGateway_depth << "}\n";
  return total_list.str();
}
void set_num (int num , int* class_num) {
  (*class_num) = (*class_num) > num ? (*class_num) : num;
}
void set_string(std::string list, std::string* class_list) {
  (*class_list) = list;
}
  public:
    int dataIn_V_data_V_depth;
    int dataIn_V_keep_V_depth;
    int dataIn_V_strb_V_depth;
    int dataIn_V_last_V_depth;
    int dataOut_V_data_V_depth;
    int dataOut_V_keep_V_depth;
    int dataOut_V_strb_V_depth;
    int dataOut_V_last_V_depth;
    int arpTableReplay_V_depth;
    int arpTableRequest_V_depth;
    int myMacAddress_depth;
    int regSubNetMask_depth;
    int regDefaultGateway_depth;
    int trans_num;
  private:
    ofstream mFile;
    const char* mName;
};

static void RTLOutputCheckAndReplacement(std::string &AESL_token, std::string PortName) {
  bool no_x = false;
  bool err = false;

  no_x = false;
  // search and replace 'X' with '0' from the 3rd char of token
  while (!no_x) {
    size_t x_found = AESL_token.find('X', 0);
    if (x_found != string::npos) {
      if (!err) { 
        cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port" 
             << PortName << ", possible cause: There are uninitialized variables in the C design."
             << endl; 
        err = true;
      }
      AESL_token.replace(x_found, 1, "0");
    } else
      no_x = true;
  }
  no_x = false;
  // search and replace 'x' with '0' from the 3rd char of token
  while (!no_x) {
    size_t x_found = AESL_token.find('x', 2);
    if (x_found != string::npos) {
      if (!err) { 
        cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' on port" 
             << PortName << ", possible cause: There are uninitialized variables in the C design."
             << endl; 
        err = true;
      }
      AESL_token.replace(x_found, 1, "0");
    } else
      no_x = true;
  }
}
struct __cosim_s40__ { char data[64]; };
struct __cosim_s10__ { char data[16]; };
struct __cosim_s4__ { char data[4]; };
extern "C" void ethernet_header_inserter_hw_stub_wrapper(volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *);

extern "C" void apatb_ethernet_header_inserter_hw(volatile void * __xlx_apatb_param_dataIn_V_data_V, volatile void * __xlx_apatb_param_dataIn_V_keep_V, volatile void * __xlx_apatb_param_dataIn_V_strb_V, volatile void * __xlx_apatb_param_dataIn_V_last_V, volatile void * __xlx_apatb_param_dataOut_V_data_V, volatile void * __xlx_apatb_param_dataOut_V_keep_V, volatile void * __xlx_apatb_param_dataOut_V_strb_V, volatile void * __xlx_apatb_param_dataOut_V_last_V, volatile void * __xlx_apatb_param_arpTableReplay, volatile void * __xlx_apatb_param_arpTableRequest, volatile void * __xlx_apatb_param_myMacAddress, volatile void * __xlx_apatb_param_regSubNetMask, volatile void * __xlx_apatb_param_regDefaultGateway) {
  refine_signal_handler();
  fstream wrapc_switch_file_token;
  wrapc_switch_file_token.open(".hls_cosim_wrapc_switch.log");
  int AESL_i;
  if (wrapc_switch_file_token.good())
  {

    CodeState = ENTER_WRAPC_PC;
    static unsigned AESL_transaction_pc = 0;
    string AESL_token;
    string AESL_num;long __xlx_apatb_param_dataIn_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_dataIn_V_data_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_dataIn_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_dataIn_stream_buf_final_size; ++i) {
((hls::stream<__cosim_s40__>*)__xlx_apatb_param_dataIn_V_data_V)->read();
((hls::stream<long long>*)__xlx_apatb_param_dataIn_V_keep_V)->read();
((hls::stream<long long>*)__xlx_apatb_param_dataIn_V_strb_V)->read();
((hls::stream<char>*)__xlx_apatb_param_dataIn_V_last_V)->read();
}
{unsigned xlx_stream_dataOut_size = 0;

          std::vector<sc_bv<512> > dataOut_V_data_V_pc_buffer_Copy;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_dataOut_V_data_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<512> > dataOut_V_data_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "dataOut");
  
            // push token into output port buffer
            if (AESL_token != "") {
              dataOut_V_data_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {xlx_stream_dataOut_size=dataOut_V_data_V_pc_buffer.size();
dataOut_V_data_V_pc_buffer_Copy=dataOut_V_data_V_pc_buffer;
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
          std::vector<sc_bv<512> > dataOut_V_keep_V_pc_buffer_Copy;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_dataOut_V_keep_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<512> > dataOut_V_keep_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "dataOut");
  
            // push token into output port buffer
            if (AESL_token != "") {
              dataOut_V_keep_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {xlx_stream_dataOut_size=dataOut_V_keep_V_pc_buffer.size();
dataOut_V_keep_V_pc_buffer_Copy=dataOut_V_keep_V_pc_buffer;
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
          std::vector<sc_bv<512> > dataOut_V_strb_V_pc_buffer_Copy;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_dataOut_V_strb_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<512> > dataOut_V_strb_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "dataOut");
  
            // push token into output port buffer
            if (AESL_token != "") {
              dataOut_V_strb_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {xlx_stream_dataOut_size=dataOut_V_strb_V_pc_buffer.size();
dataOut_V_strb_V_pc_buffer_Copy=dataOut_V_strb_V_pc_buffer;
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
          std::vector<sc_bv<512> > dataOut_V_last_V_pc_buffer_Copy;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_dataOut_V_last_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<512> > dataOut_V_last_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "dataOut");
  
            // push token into output port buffer
            if (AESL_token != "") {
              dataOut_V_last_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {xlx_stream_dataOut_size=dataOut_V_last_V_pc_buffer.size();
dataOut_V_last_V_pc_buffer_Copy=dataOut_V_last_V_pc_buffer;
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (int j = 0, e = xlx_stream_dataOut_size; j != e; ++j) {
__cosim_s40__ xlx_stream_elt_data;
((long long*)&xlx_stream_elt_data)[0*8+0] = dataOut_V_data_V_pc_buffer_Copy[j].range(63,0).to_int64();
((long long*)&xlx_stream_elt_data)[0*8+1] = dataOut_V_data_V_pc_buffer_Copy[j].range(127,64).to_int64();
((long long*)&xlx_stream_elt_data)[0*8+2] = dataOut_V_data_V_pc_buffer_Copy[j].range(191,128).to_int64();
((long long*)&xlx_stream_elt_data)[0*8+3] = dataOut_V_data_V_pc_buffer_Copy[j].range(255,192).to_int64();
((long long*)&xlx_stream_elt_data)[0*8+4] = dataOut_V_data_V_pc_buffer_Copy[j].range(319,256).to_int64();
((long long*)&xlx_stream_elt_data)[0*8+5] = dataOut_V_data_V_pc_buffer_Copy[j].range(383,320).to_int64();
((long long*)&xlx_stream_elt_data)[0*8+6] = dataOut_V_data_V_pc_buffer_Copy[j].range(447,384).to_int64();
((long long*)&xlx_stream_elt_data)[0*8+7] = dataOut_V_data_V_pc_buffer_Copy[j].range(511,448).to_int64();
((hls::stream<__cosim_s40__>*)__xlx_apatb_param_dataOut_V_data_V)->write(xlx_stream_elt_data);
long long xlx_stream_elt_keep;
((long long*)&xlx_stream_elt_keep)[0] = dataOut_V_keep_V_pc_buffer_Copy[j].to_int64();
((hls::stream<long long>*)__xlx_apatb_param_dataOut_V_keep_V)->write(xlx_stream_elt_keep);
long long xlx_stream_elt_strb;
((long long*)&xlx_stream_elt_strb)[0] = dataOut_V_strb_V_pc_buffer_Copy[j].to_int64();
((hls::stream<long long>*)__xlx_apatb_param_dataOut_V_strb_V)->write(xlx_stream_elt_strb);
char xlx_stream_elt_last;
((char*)&xlx_stream_elt_last)[0] = dataOut_V_last_V_pc_buffer_Copy[j].to_uint64();
((hls::stream<char>*)__xlx_apatb_param_dataOut_V_last_V)->write(xlx_stream_elt_last);
}}long __xlx_apatb_param_arpTableReplay_V_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_arpTableReplay_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_arpTableReplay_V_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_arpTableReplay_V_stream_buf_final_size; ++i)((hls::stream<__cosim_s10__>*)__xlx_apatb_param_arpTableReplay)->read();
long __xlx_apatb_param_arpTableRequest_V_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_OUT_arpTableRequest_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_arpTableRequest_V_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_arpTableRequest_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<32> > arpTableRequest_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "arpTableRequest_V");
  
            // push token into output port buffer
            if (AESL_token != "") {
              arpTableRequest_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {for (int j = 0, e = i; j != e; ++j) {
__cosim_s4__ xlx_stream_elt;
((char*)&xlx_stream_elt)[0*4+0] = arpTableRequest_V_pc_buffer[j].range(7, 0).to_int64();
((char*)&xlx_stream_elt)[0*4+1] = arpTableRequest_V_pc_buffer[j].range(15, 8).to_int64();
((char*)&xlx_stream_elt)[0*4+2] = arpTableRequest_V_pc_buffer[j].range(23, 16).to_int64();
((char*)&xlx_stream_elt)[0*4+3] = arpTableRequest_V_pc_buffer[j].range(31, 24).to_int64();
((hls::stream<__cosim_s4__>*)__xlx_apatb_param_arpTableRequest)->write(xlx_stream_elt);
}
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
    AESL_transaction_pc++;
    return ;
  }
static unsigned AESL_transaction;
static AESL_FILE_HANDLER aesl_fh;
static INTER_TCL_FILE tcl_file(INTER_TCL);
std::vector<char> __xlx_sprintf_buffer(1024);
CodeState = ENTER_WRAPC;
//dataIn
aesl_fh.touch(AUTOTB_TVIN_dataIn_V_data_V);
aesl_fh.touch(AUTOTB_TVOUT_dataIn_V_data_V);
aesl_fh.touch(AUTOTB_TVIN_dataIn_V_keep_V);
aesl_fh.touch(AUTOTB_TVOUT_dataIn_V_keep_V);
aesl_fh.touch(AUTOTB_TVIN_dataIn_V_strb_V);
aesl_fh.touch(AUTOTB_TVOUT_dataIn_V_strb_V);
aesl_fh.touch(AUTOTB_TVIN_dataIn_V_last_V);
aesl_fh.touch(AUTOTB_TVOUT_dataIn_V_last_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_dataIn_V_data_V);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_dataIn_V_data_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_dataIn_V_keep_V);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_dataIn_V_keep_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_dataIn_V_strb_V);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_dataIn_V_strb_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_dataIn_V_last_V);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_dataIn_V_last_V);
//dataOut
aesl_fh.touch(AUTOTB_TVIN_dataOut_V_data_V);
aesl_fh.touch(AUTOTB_TVOUT_dataOut_V_data_V);
aesl_fh.touch(AUTOTB_TVIN_dataOut_V_keep_V);
aesl_fh.touch(AUTOTB_TVOUT_dataOut_V_keep_V);
aesl_fh.touch(AUTOTB_TVIN_dataOut_V_strb_V);
aesl_fh.touch(AUTOTB_TVOUT_dataOut_V_strb_V);
aesl_fh.touch(AUTOTB_TVIN_dataOut_V_last_V);
aesl_fh.touch(AUTOTB_TVOUT_dataOut_V_last_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_dataOut_V_data_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_dataOut_V_data_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_dataOut_V_keep_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_dataOut_V_keep_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_dataOut_V_strb_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_dataOut_V_strb_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_dataOut_V_last_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_dataOut_V_last_V);
//arpTableReplay_V
aesl_fh.touch(AUTOTB_TVIN_arpTableReplay_V);
aesl_fh.touch(AUTOTB_TVOUT_arpTableReplay_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_arpTableReplay_V);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_arpTableReplay_V);
//arpTableRequest_V
aesl_fh.touch(AUTOTB_TVIN_arpTableRequest_V);
aesl_fh.touch(AUTOTB_TVOUT_arpTableRequest_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_arpTableRequest_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_arpTableRequest_V);
//myMacAddress
aesl_fh.touch(AUTOTB_TVIN_myMacAddress);
aesl_fh.touch(AUTOTB_TVOUT_myMacAddress);
//regSubNetMask
aesl_fh.touch(AUTOTB_TVIN_regSubNetMask);
aesl_fh.touch(AUTOTB_TVOUT_regSubNetMask);
//regDefaultGateway
aesl_fh.touch(AUTOTB_TVIN_regDefaultGateway);
aesl_fh.touch(AUTOTB_TVOUT_regDefaultGateway);
CodeState = DUMP_INPUTS;
// data
std::vector<__cosim_s40__> __xlx_apatb_param_dataIn_V_data_V_stream_buf;
{
  while (!((hls::stream<__cosim_s40__>*)__xlx_apatb_param_dataIn_V_data_V)->empty())
    __xlx_apatb_param_dataIn_V_data_V_stream_buf.push_back(((hls::stream<__cosim_s40__>*)__xlx_apatb_param_dataIn_V_data_V)->read());
  for (int i = 0; i < __xlx_apatb_param_dataIn_V_data_V_stream_buf.size(); ++i)
    ((hls::stream<__cosim_s40__>*)__xlx_apatb_param_dataIn_V_data_V)->write(__xlx_apatb_param_dataIn_V_data_V_stream_buf[i]);
  }
long __xlx_apatb_param_dataIn_stream_buf_size = ((hls::stream<__cosim_s40__>*)__xlx_apatb_param_dataIn_V_data_V)->size();
// keep
std::vector<long long> __xlx_apatb_param_dataIn_V_keep_V_stream_buf;
{
  while (!((hls::stream<long long>*)__xlx_apatb_param_dataIn_V_keep_V)->empty())
    __xlx_apatb_param_dataIn_V_keep_V_stream_buf.push_back(((hls::stream<long long>*)__xlx_apatb_param_dataIn_V_keep_V)->read());
  for (int i = 0; i < __xlx_apatb_param_dataIn_V_keep_V_stream_buf.size(); ++i)
    ((hls::stream<long long>*)__xlx_apatb_param_dataIn_V_keep_V)->write(__xlx_apatb_param_dataIn_V_keep_V_stream_buf[i]);
  }
// strb
std::vector<long long> __xlx_apatb_param_dataIn_V_strb_V_stream_buf;
{
  while (!((hls::stream<long long>*)__xlx_apatb_param_dataIn_V_strb_V)->empty())
    __xlx_apatb_param_dataIn_V_strb_V_stream_buf.push_back(((hls::stream<long long>*)__xlx_apatb_param_dataIn_V_strb_V)->read());
  for (int i = 0; i < __xlx_apatb_param_dataIn_V_strb_V_stream_buf.size(); ++i)
    ((hls::stream<long long>*)__xlx_apatb_param_dataIn_V_strb_V)->write(__xlx_apatb_param_dataIn_V_strb_V_stream_buf[i]);
  }
// user
// last
std::vector<char> __xlx_apatb_param_dataIn_V_last_V_stream_buf;
{
  while (!((hls::stream<char>*)__xlx_apatb_param_dataIn_V_last_V)->empty())
    __xlx_apatb_param_dataIn_V_last_V_stream_buf.push_back(((hls::stream<char>*)__xlx_apatb_param_dataIn_V_last_V)->read());
  for (int i = 0; i < __xlx_apatb_param_dataIn_V_last_V_stream_buf.size(); ++i)
    ((hls::stream<char>*)__xlx_apatb_param_dataIn_V_last_V)->write(__xlx_apatb_param_dataIn_V_last_V_stream_buf[i]);
  }
// id
// dest
// data
std::vector<__cosim_s40__> __xlx_apatb_param_dataOut_V_data_V_stream_buf;
long __xlx_apatb_param_dataOut_stream_buf_size = ((hls::stream<__cosim_s40__>*)__xlx_apatb_param_dataOut_V_data_V)->size();
// keep
std::vector<long long> __xlx_apatb_param_dataOut_V_keep_V_stream_buf;
// strb
std::vector<long long> __xlx_apatb_param_dataOut_V_strb_V_stream_buf;
// user
// last
std::vector<char> __xlx_apatb_param_dataOut_V_last_V_stream_buf;
// id
// dest
std::vector<__cosim_s10__> __xlx_apatb_param_arpTableReplay_stream_buf;
{
  while (!((hls::stream<__cosim_s10__>*)__xlx_apatb_param_arpTableReplay)->empty())
    __xlx_apatb_param_arpTableReplay_stream_buf.push_back(((hls::stream<__cosim_s10__>*)__xlx_apatb_param_arpTableReplay)->read());
  for (int i = 0; i < __xlx_apatb_param_arpTableReplay_stream_buf.size(); ++i)
    ((hls::stream<__cosim_s10__>*)__xlx_apatb_param_arpTableReplay)->write(__xlx_apatb_param_arpTableReplay_stream_buf[i]);
  }
long __xlx_apatb_param_arpTableReplay_stream_buf_size = ((hls::stream<__cosim_s10__>*)__xlx_apatb_param_arpTableReplay)->size();
std::vector<__cosim_s4__> __xlx_apatb_param_arpTableRequest_stream_buf;
long __xlx_apatb_param_arpTableRequest_stream_buf_size = ((hls::stream<__cosim_s4__>*)__xlx_apatb_param_arpTableRequest)->size();
// print myMacAddress Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_myMacAddress, __xlx_sprintf_buffer.data());
  {
    sc_bv<48> __xlx_tmp_lv = *((long long*)__xlx_apatb_param_myMacAddress);

    std::string s(__xlx_tmp_lv.to_string(SC_HEX));
    aesl_fh.write(AUTOTB_TVIN_myMacAddress, s.append("\n")); 
  }
  tcl_file.set_num(1, &tcl_file.myMacAddress_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_myMacAddress, __xlx_sprintf_buffer.data());
}
// print regSubNetMask Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_regSubNetMask, __xlx_sprintf_buffer.data());
  {
    sc_bv<32> __xlx_tmp_lv = *((int*)__xlx_apatb_param_regSubNetMask);

    std::string s(__xlx_tmp_lv.to_string(SC_HEX));
    aesl_fh.write(AUTOTB_TVIN_regSubNetMask, s.append("\n")); 
  }
  tcl_file.set_num(1, &tcl_file.regSubNetMask_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_regSubNetMask, __xlx_sprintf_buffer.data());
}
// print regDefaultGateway Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_regDefaultGateway, __xlx_sprintf_buffer.data());
  {
    sc_bv<32> __xlx_tmp_lv = *((int*)__xlx_apatb_param_regDefaultGateway);

    std::string s(__xlx_tmp_lv.to_string(SC_HEX));
    aesl_fh.write(AUTOTB_TVIN_regDefaultGateway, s.append("\n")); 
  }
  tcl_file.set_num(1, &tcl_file.regDefaultGateway_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_regDefaultGateway, __xlx_sprintf_buffer.data());
}
CodeState = CALL_C_DUT;
ethernet_header_inserter_hw_stub_wrapper(__xlx_apatb_param_dataIn_V_data_V, __xlx_apatb_param_dataIn_V_keep_V, __xlx_apatb_param_dataIn_V_strb_V, __xlx_apatb_param_dataIn_V_last_V, __xlx_apatb_param_dataOut_V_data_V, __xlx_apatb_param_dataOut_V_keep_V, __xlx_apatb_param_dataOut_V_strb_V, __xlx_apatb_param_dataOut_V_last_V, __xlx_apatb_param_arpTableReplay, __xlx_apatb_param_arpTableRequest, __xlx_apatb_param_myMacAddress, __xlx_apatb_param_regSubNetMask, __xlx_apatb_param_regDefaultGateway);
CodeState = DUMP_OUTPUTS;
long __xlx_apatb_param_dataIn_stream_buf_final_size = __xlx_apatb_param_dataIn_stream_buf_size - ((hls::stream<__cosim_s40__>*)__xlx_apatb_param_dataIn_V_data_V)->size();

  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_dataIn_V_data_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_dataIn_V_keep_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_dataIn_V_strb_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_dataIn_V_last_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_dataIn_stream_buf_final_size; j != e; ++j) {
sc_bv<512> __xlx_tmp_0_lv;
{
sc_bv<512> __xlx_tmp_lv;
__xlx_tmp_lv.range(63,0) = ((long long*)&__xlx_apatb_param_dataIn_V_data_V_stream_buf[j])[0*8+0];
__xlx_tmp_lv.range(127,64) = ((long long*)&__xlx_apatb_param_dataIn_V_data_V_stream_buf[j])[0*8+1];
__xlx_tmp_lv.range(191,128) = ((long long*)&__xlx_apatb_param_dataIn_V_data_V_stream_buf[j])[0*8+2];
__xlx_tmp_lv.range(255,192) = ((long long*)&__xlx_apatb_param_dataIn_V_data_V_stream_buf[j])[0*8+3];
__xlx_tmp_lv.range(319,256) = ((long long*)&__xlx_apatb_param_dataIn_V_data_V_stream_buf[j])[0*8+4];
__xlx_tmp_lv.range(383,320) = ((long long*)&__xlx_apatb_param_dataIn_V_data_V_stream_buf[j])[0*8+5];
__xlx_tmp_lv.range(447,384) = ((long long*)&__xlx_apatb_param_dataIn_V_data_V_stream_buf[j])[0*8+6];
__xlx_tmp_lv.range(511,448) = ((long long*)&__xlx_apatb_param_dataIn_V_data_V_stream_buf[j])[0*8+7];
__xlx_tmp_0_lv = __xlx_tmp_lv;
}
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_0_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVIN_dataIn_V_data_V, __xlx_sprintf_buffer.data());
sc_bv<64> __xlx_tmp_1_lv = ((long long*)&__xlx_apatb_param_dataIn_V_keep_V_stream_buf[j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_1_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVIN_dataIn_V_keep_V, __xlx_sprintf_buffer.data());
sc_bv<64> __xlx_tmp_2_lv = ((long long*)&__xlx_apatb_param_dataIn_V_strb_V_stream_buf[j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_2_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVIN_dataIn_V_strb_V, __xlx_sprintf_buffer.data());
sc_bv<1> __xlx_tmp_4_lv = ((char*)&__xlx_apatb_param_dataIn_V_last_V_stream_buf[j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_4_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVIN_dataIn_V_last_V, __xlx_sprintf_buffer.data());
}
tcl_file.set_num(__xlx_apatb_param_dataIn_stream_buf_final_size, &tcl_file.dataIn_V_data_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_dataIn_V_data_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_dataIn_stream_buf_final_size, &tcl_file.dataIn_V_keep_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_dataIn_V_keep_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_dataIn_stream_buf_final_size, &tcl_file.dataIn_V_strb_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_dataIn_V_strb_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_dataIn_stream_buf_final_size, &tcl_file.dataIn_V_last_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_dataIn_V_last_V, __xlx_sprintf_buffer.data());

// dump stream ingress status to file

// dump stream ingress status to file
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_dataIn_V_data_V, __xlx_sprintf_buffer.data());
  if (__xlx_apatb_param_dataIn_stream_buf_final_size > 0) {
  long dataIn_V_data_V_stream_ingress_size = __xlx_apatb_param_dataIn_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", dataIn_V_data_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_dataIn_V_data_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_dataIn_stream_buf_final_size; j != e; j++) {
    dataIn_V_data_V_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", dataIn_V_data_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_dataIn_V_data_V, __xlx_sprintf_buffer.data());
  }
} else {
  long dataIn_V_data_V_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", dataIn_V_data_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_dataIn_V_data_V, __xlx_sprintf_buffer.data());
}

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_dataIn_V_data_V, __xlx_sprintf_buffer.data());
}
// dump stream ingress status to file
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_dataIn_V_keep_V, __xlx_sprintf_buffer.data());
  if (__xlx_apatb_param_dataIn_stream_buf_final_size > 0) {
  long dataIn_V_keep_V_stream_ingress_size = __xlx_apatb_param_dataIn_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", dataIn_V_keep_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_dataIn_V_keep_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_dataIn_stream_buf_final_size; j != e; j++) {
    dataIn_V_keep_V_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", dataIn_V_keep_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_dataIn_V_keep_V, __xlx_sprintf_buffer.data());
  }
} else {
  long dataIn_V_keep_V_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", dataIn_V_keep_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_dataIn_V_keep_V, __xlx_sprintf_buffer.data());
}

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_dataIn_V_keep_V, __xlx_sprintf_buffer.data());
}
// dump stream ingress status to file
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_dataIn_V_strb_V, __xlx_sprintf_buffer.data());
  if (__xlx_apatb_param_dataIn_stream_buf_final_size > 0) {
  long dataIn_V_strb_V_stream_ingress_size = __xlx_apatb_param_dataIn_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", dataIn_V_strb_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_dataIn_V_strb_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_dataIn_stream_buf_final_size; j != e; j++) {
    dataIn_V_strb_V_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", dataIn_V_strb_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_dataIn_V_strb_V, __xlx_sprintf_buffer.data());
  }
} else {
  long dataIn_V_strb_V_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", dataIn_V_strb_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_dataIn_V_strb_V, __xlx_sprintf_buffer.data());
}

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_dataIn_V_strb_V, __xlx_sprintf_buffer.data());
}
// dump stream ingress status to file
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_dataIn_V_last_V, __xlx_sprintf_buffer.data());
  if (__xlx_apatb_param_dataIn_stream_buf_final_size > 0) {
  long dataIn_V_last_V_stream_ingress_size = __xlx_apatb_param_dataIn_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", dataIn_V_last_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_dataIn_V_last_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_dataIn_stream_buf_final_size; j != e; j++) {
    dataIn_V_last_V_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", dataIn_V_last_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_dataIn_V_last_V, __xlx_sprintf_buffer.data());
  }
} else {
  long dataIn_V_last_V_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", dataIn_V_last_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_dataIn_V_last_V, __xlx_sprintf_buffer.data());
}

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_dataIn_V_last_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_dataIn_V_data_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_dataIn_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_dataIn_V_data_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_dataIn_V_data_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_dataIn_V_keep_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_dataIn_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_dataIn_V_keep_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_dataIn_V_keep_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_dataIn_V_strb_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_dataIn_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_dataIn_V_strb_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_dataIn_V_strb_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_dataIn_V_last_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_dataIn_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_dataIn_V_last_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_dataIn_V_last_V, __xlx_sprintf_buffer.data());
}
//********************** dump C output stream *******************
long __xlx_apatb_param_dataOut_stream_buf_final_size = ((hls::stream<__cosim_s40__>*)__xlx_apatb_param_dataOut_V_data_V)->size() - __xlx_apatb_param_dataOut_stream_buf_size;
{
  while (!((hls::stream<__cosim_s40__>*)__xlx_apatb_param_dataOut_V_data_V)->empty())
    __xlx_apatb_param_dataOut_V_data_V_stream_buf.push_back(((hls::stream<__cosim_s40__>*)__xlx_apatb_param_dataOut_V_data_V)->read());
  for (int i = 0; i < __xlx_apatb_param_dataOut_V_data_V_stream_buf.size(); ++i)
    ((hls::stream<__cosim_s40__>*)__xlx_apatb_param_dataOut_V_data_V)->write(__xlx_apatb_param_dataOut_V_data_V_stream_buf[i]);
  }
{
  while (!((hls::stream<long long>*)__xlx_apatb_param_dataOut_V_keep_V)->empty())
    __xlx_apatb_param_dataOut_V_keep_V_stream_buf.push_back(((hls::stream<long long>*)__xlx_apatb_param_dataOut_V_keep_V)->read());
  for (int i = 0; i < __xlx_apatb_param_dataOut_V_keep_V_stream_buf.size(); ++i)
    ((hls::stream<long long>*)__xlx_apatb_param_dataOut_V_keep_V)->write(__xlx_apatb_param_dataOut_V_keep_V_stream_buf[i]);
  }
{
  while (!((hls::stream<long long>*)__xlx_apatb_param_dataOut_V_strb_V)->empty())
    __xlx_apatb_param_dataOut_V_strb_V_stream_buf.push_back(((hls::stream<long long>*)__xlx_apatb_param_dataOut_V_strb_V)->read());
  for (int i = 0; i < __xlx_apatb_param_dataOut_V_strb_V_stream_buf.size(); ++i)
    ((hls::stream<long long>*)__xlx_apatb_param_dataOut_V_strb_V)->write(__xlx_apatb_param_dataOut_V_strb_V_stream_buf[i]);
  }
{
  while (!((hls::stream<char>*)__xlx_apatb_param_dataOut_V_last_V)->empty())
    __xlx_apatb_param_dataOut_V_last_V_stream_buf.push_back(((hls::stream<char>*)__xlx_apatb_param_dataOut_V_last_V)->read());
  for (int i = 0; i < __xlx_apatb_param_dataOut_V_last_V_stream_buf.size(); ++i)
    ((hls::stream<char>*)__xlx_apatb_param_dataOut_V_last_V)->write(__xlx_apatb_param_dataOut_V_last_V_stream_buf[i]);
  }

  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_dataOut_V_data_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_dataOut_V_keep_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_dataOut_V_strb_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_dataOut_V_last_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_dataOut_stream_buf_final_size; j != e; ++j) {
sc_bv<512> __xlx_tmp_0_lv;
{
sc_bv<512> __xlx_tmp_lv;
__xlx_tmp_lv.range(63,0) = ((long long*)&__xlx_apatb_param_dataOut_V_data_V_stream_buf[__xlx_apatb_param_dataOut_stream_buf_size+j])[0*8+0];
__xlx_tmp_lv.range(127,64) = ((long long*)&__xlx_apatb_param_dataOut_V_data_V_stream_buf[__xlx_apatb_param_dataOut_stream_buf_size+j])[0*8+1];
__xlx_tmp_lv.range(191,128) = ((long long*)&__xlx_apatb_param_dataOut_V_data_V_stream_buf[__xlx_apatb_param_dataOut_stream_buf_size+j])[0*8+2];
__xlx_tmp_lv.range(255,192) = ((long long*)&__xlx_apatb_param_dataOut_V_data_V_stream_buf[__xlx_apatb_param_dataOut_stream_buf_size+j])[0*8+3];
__xlx_tmp_lv.range(319,256) = ((long long*)&__xlx_apatb_param_dataOut_V_data_V_stream_buf[__xlx_apatb_param_dataOut_stream_buf_size+j])[0*8+4];
__xlx_tmp_lv.range(383,320) = ((long long*)&__xlx_apatb_param_dataOut_V_data_V_stream_buf[__xlx_apatb_param_dataOut_stream_buf_size+j])[0*8+5];
__xlx_tmp_lv.range(447,384) = ((long long*)&__xlx_apatb_param_dataOut_V_data_V_stream_buf[__xlx_apatb_param_dataOut_stream_buf_size+j])[0*8+6];
__xlx_tmp_lv.range(511,448) = ((long long*)&__xlx_apatb_param_dataOut_V_data_V_stream_buf[__xlx_apatb_param_dataOut_stream_buf_size+j])[0*8+7];
__xlx_tmp_0_lv = __xlx_tmp_lv;
}
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_0_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVOUT_dataOut_V_data_V, __xlx_sprintf_buffer.data());
sc_bv<64> __xlx_tmp_1_lv = ((long long*)&__xlx_apatb_param_dataOut_V_keep_V_stream_buf[__xlx_apatb_param_dataOut_stream_buf_size+j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_1_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVOUT_dataOut_V_keep_V, __xlx_sprintf_buffer.data());
sc_bv<64> __xlx_tmp_2_lv = ((long long*)&__xlx_apatb_param_dataOut_V_strb_V_stream_buf[__xlx_apatb_param_dataOut_stream_buf_size+j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_2_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVOUT_dataOut_V_strb_V, __xlx_sprintf_buffer.data());
sc_bv<1> __xlx_tmp_4_lv = ((char*)&__xlx_apatb_param_dataOut_V_last_V_stream_buf[__xlx_apatb_param_dataOut_stream_buf_size+j])[0];
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_4_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVOUT_dataOut_V_last_V, __xlx_sprintf_buffer.data());
}
tcl_file.set_num(__xlx_apatb_param_dataOut_stream_buf_final_size, &tcl_file.dataOut_V_data_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_dataOut_V_data_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_dataOut_stream_buf_final_size, &tcl_file.dataOut_V_keep_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_dataOut_V_keep_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_dataOut_stream_buf_final_size, &tcl_file.dataOut_V_strb_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_dataOut_V_strb_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_dataOut_stream_buf_final_size, &tcl_file.dataOut_V_last_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_dataOut_V_last_V, __xlx_sprintf_buffer.data());
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_dataOut_V_data_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_dataOut_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_dataOut_V_data_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_dataOut_V_data_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_dataOut_V_keep_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_dataOut_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_dataOut_V_keep_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_dataOut_V_keep_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_dataOut_V_strb_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_dataOut_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_dataOut_V_strb_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_dataOut_V_strb_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_dataOut_V_last_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_dataOut_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_dataOut_V_last_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_dataOut_V_last_V, __xlx_sprintf_buffer.data());
}long __xlx_apatb_param_arpTableReplay_stream_buf_final_size = __xlx_apatb_param_arpTableReplay_stream_buf_size - ((hls::stream<__cosim_s10__>*)__xlx_apatb_param_arpTableReplay)->size();
// print arpTableReplay_V Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_arpTableReplay_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_arpTableReplay_stream_buf_final_size; j != e; ++j) {
sc_bv<128> __xlx_tmp_lv_hw;
sc_bv<128> __xlx_tmp_lv;
__xlx_tmp_lv.range(63,0) = ((long long*)&__xlx_apatb_param_arpTableReplay_stream_buf[j])[0*2+0];
__xlx_tmp_lv.range(127,64) = ((long long*)&__xlx_apatb_param_arpTableReplay_stream_buf[j])[0*2+1];
__xlx_tmp_lv_hw = __xlx_tmp_lv;

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv_hw.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_arpTableReplay_V, __xlx_sprintf_buffer.data()); 
  }

  tcl_file.set_num(__xlx_apatb_param_arpTableReplay_stream_buf_final_size, &tcl_file.arpTableReplay_V_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_arpTableReplay_V, __xlx_sprintf_buffer.data());
}

// dump stream ingress status to file
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_arpTableReplay_V, __xlx_sprintf_buffer.data());
  if (__xlx_apatb_param_arpTableReplay_stream_buf_final_size > 0) {
  long arpTableReplay_V_stream_ingress_size = __xlx_apatb_param_arpTableReplay_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", arpTableReplay_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_arpTableReplay_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_arpTableReplay_stream_buf_final_size; j != e; j++) {
    arpTableReplay_V_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", arpTableReplay_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_arpTableReplay_V, __xlx_sprintf_buffer.data());
  }
} else {
  long arpTableReplay_V_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", arpTableReplay_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_arpTableReplay_V, __xlx_sprintf_buffer.data());
}

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_arpTableReplay_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_arpTableReplay_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_arpTableReplay_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_arpTableReplay_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_arpTableReplay_V, __xlx_sprintf_buffer.data());
}long __xlx_apatb_param_arpTableRequest_stream_buf_final_size = ((hls::stream<__cosim_s4__>*)__xlx_apatb_param_arpTableRequest)->size() - __xlx_apatb_param_arpTableRequest_stream_buf_size;
{
  while (!((hls::stream<__cosim_s4__>*)__xlx_apatb_param_arpTableRequest)->empty())
    __xlx_apatb_param_arpTableRequest_stream_buf.push_back(((hls::stream<__cosim_s4__>*)__xlx_apatb_param_arpTableRequest)->read());
  for (int i = 0; i < __xlx_apatb_param_arpTableRequest_stream_buf.size(); ++i)
    ((hls::stream<__cosim_s4__>*)__xlx_apatb_param_arpTableRequest)->write(__xlx_apatb_param_arpTableRequest_stream_buf[i]);
  }
// print arpTableRequest_V Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_arpTableRequest_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_arpTableRequest_stream_buf_final_size; j != e; ++j) {
sc_bv<32> __xlx_tmp_lv = ((int*)&__xlx_apatb_param_arpTableRequest_stream_buf[__xlx_apatb_param_arpTableRequest_stream_buf_size+j])[0];

    std::string s(__xlx_tmp_lv.to_string(SC_HEX));
    aesl_fh.write(AUTOTB_TVOUT_arpTableRequest_V, s.append("\n")); 
  }

  tcl_file.set_num(__xlx_apatb_param_arpTableRequest_stream_buf_final_size, &tcl_file.arpTableRequest_V_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_arpTableRequest_V, __xlx_sprintf_buffer.data());
}
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_arpTableRequest_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_arpTableRequest_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_arpTableRequest_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_arpTableRequest_V, __xlx_sprintf_buffer.data());
}CodeState = DELETE_CHAR_BUFFERS;
AESL_transaction++;
tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
}
