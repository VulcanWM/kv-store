# Key Value Store

This is a simple Key Value store in C++ which uses `unordered_map` to store the key and value.

It uses log files to store a snapshot of the current state, which is then recovered once the store is started again.

It is a fully terminal based project, and once you run the program (by doing `./kvstore [DB_NAME]`) you use the REPL to execute the commands.

The commands include:
- `SET [KEY] [VALUE]`
- `GET [KEY]`
- `DEL [KEY]`