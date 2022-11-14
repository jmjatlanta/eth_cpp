CXX_FLAGS=-Ithirdparty/rapidjson/include

%.o:%.cpp
	$(CXX) $(CXX_FLAGS) -c $^ -o $@

example/connect: example/connect.o IPCConnector.o
	$(CXX) -o $@ $^

clean:
	$(RM) *.o
	$(RM) example/connect
	$(RM) example/connect.o
