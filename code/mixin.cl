
MixinTest a = new MixinTest(123);
String b = Clover.outputToString() {
    a.method();
}

print("mixin test1...");
if(b == "I'm a non class method without parametor\nHELLO WORLD on non class method\n") {
    println("OK");
}
else {
    println("FALSE");
    System.exit(2);
}

String c = Clover.outputToString() {
    MixinTest.method();
}

print("mixin test2...");
if(c == "I'm a class method with parametor\nHELLO WORLD on class method\n") {
    println("OK");
}
else {
    println("FALSE");
    System.exit(2);
}
