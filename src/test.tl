/*
TestLanguage test file
 */

import lang.io;
import lang.entrypoint.EntryPoint;
import lang.cli.CliEntry;

class Test {
    Int function() {
        return 0;
    }
}

class Main: CliEntry {
    Int onProgramStart(args: String) {
        io.stdout.println(msg: "Hello, world!");
        return 0;
    }
}
