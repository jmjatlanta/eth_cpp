CXX_FLAGS=-Ithirdparty/rapidjson/include -O0 -g -std=c++11
ETH_OBJS=EthCpp.o Eth.o types.o IPCConnector.o Web3.o Util.o Les.o
LD_FLAGS=-O0 -g

%.o:%.cpp
	$(CXX) $(CXX_FLAGS) -c $^ -o $@

all: example/connect

test/test: $(ETH_OBJS) test/test_block.o test/test_types.o test/test_web3.o test/test_les.o
	cd test; $(MAKE)

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
	$(RM) example/*.o
	cd test; make clean
