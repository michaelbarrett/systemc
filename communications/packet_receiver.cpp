//packet_receiver.cpp
#include "packet_receiver.h"

void packet_receiver :: prc_packet_receiver() { //synch. -- deals with vars
  var_in_data =  in_data.read() ;
  
  if (reset) {
    //increase var count depending on in_data.read()
    if (var_in_data.range(11,8) == "0001") {
      //if the header is 0001, then inc
      var_count = var_count + 1;
    }
    //increase var error depending on in_data.read()
    //use concatenation and xor_reduce
    if ((var_in_data.range(7,4).xor_reduce() == '0'

	 & var_in_data[0] == '0')) { //wrong!
      //if the data payload's of even parity and the in_data is thus incorrect (0)
      var_error = var_error + 1;
    }
    else if ((var_in_data.range(7,4).xor_reduce() == '1'
	      
	      & in_data.read()[0] == '1')) { //wrong!
      var_error = var_error + 1;
    }
  }
  else { //reset is asserted
    var_count = 0;
    var_error = 0;
  }
}

void packet_receiver :: prc_output() { //comb. -- deals with outp
  if (!clear) {    
    if (var_in_data.range(11,8) == "0001") {
      //if the header is 0001, then it is type 1 and so we outp the payload
      payload.write( (var_in_data.range(7,4)) );
    }
    //output the outp vars from the signals
    count.write(var_count);
    error.write(var_error);
  }
}
