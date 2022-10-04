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

mixin CliEntry: EntryPoint {
    @essential Int onProgramStart(args: String);
    @optional Void onInterrupt(code: Int);
}

class Main: CliEntry {
    Int someInteger = 0;
    String someString = "Hello, world!";
    Test someTestClass = Test();

    Int onProgramStart(args: String) {
        io.stdout.println(msg: someString);
        someTestClass.function();
        someTestClass.functionWithArgs(arg1: 1, arg2: 2, arg3: 3);

        someInteger += 10;
        someString = "Hello, world!";

        someInteger = someInteger + 10;

        return 0;
    }

    Void onInterrupt(code: Int) {
        io.stdout.println(msg: "Interrupted with code \(code)");
        return 0;
    }
}
