CXX_FLAGS=-Ithirdparty/rapidjson/include -O0 -g -std=c++11
ETH_OBJS=EthCpp.o Eth.o types.o IPCConnector.o Web3.o Util.o
LD_FLAGS=-O0 -g

%.o:%.cpp
	$(CXX) $(CXX_FLAGS) -c $^ -o $@

all: example/connect example/test_block example/test_web3 example/test_types

example/connect: example/connect.o $(ETH_OBJS)
	$(CXX) $(LD_FLAGS) -o $@ $^

example/test_block: example/test_block.o $(ETH_OBJS)
	$(CXX) $(LD_FLAGS) -o $@ $^

example/test_web3: example/test_web3.o $(ETH_OBJS)
	$(CXX) $(LD_FLAGS) -o $@ $^

example/test_types: example/test_types.o $(ETH_OBJS)
	$(CXX) $(LD_FLAGS) -o $@ $^

clean:
	$(RM) *.o
	$(RM) example/connect
	$(RM) example/test_block
	$(RM) example/test_web3
	$(RM) example/test_types
	$(RM) example/*.o
