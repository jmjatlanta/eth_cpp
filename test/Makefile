CXX_FLAGS=-I../thirdparty/rapidjson/include -O0 -g -std=c++11
ETH_OBJS=../EthCpp.o ../Eth.o ../types.o ../IPCConnector.o ../Web3.o ../Util.o ../Les.o
LD_FLAGS=-O0 -g

%.o:%.cpp
	$(CXX) $(CXX_FLAGS) -c $^ -o $@

.PHONY: test

all: test

test: $(ETH_OBJS) test_block.o test_web3.o test_types.o test_les.o
	$(CXX) $(LD_FLAGS) -o $@ $^ -lgtest -lgtest_main

clean:
	$(RM) *.o
	$(RM) test
