
A a = new A();

IBase b = a;

print("interface test...");
if(b.get_field1(123) == 111 && b.get_field2() == 222 && b.get_field3(123,456) == 333) {
    println("TRUE");
}
else {
    println("FALSE");
    System.exit(1);
}

IBase3 c = a;

print("interface test2...");
if(c.get_field5() == 555) {
    println("TRUE");
}
else {
    println("FALSE");
    System.exit(1);
}

IBase2 d = c;

print("interface test3...");
if(d.get_field4() == 444) {
    println("TRUE");
}
else {
    println("FALSE");
    System.exit(1);
}

IBase2 e = a;

print("interface test4...");
if(d.get_field4() == 444) {
    println("TRUE");
}
else {
    println("FALSE");
    System.exit(1);
}
