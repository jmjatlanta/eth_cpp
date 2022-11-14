## Connect to Ethereum IPC

This is a quick example on how to connect to Ethereum's `geth` client via C++ and IPC. 

The class `IPCConnector` is an RAII-style wrapper around C POSIX socket code.

The `connector`example in the `examples` directory shows a basic connect and disconnect.
Parsing the incoming JSON is done using [RapidJson](https://github.com/Tencent/rapidjson).

Future directions could include wrapping the JSON-RPC calls into something more API like, so stay tuned.
