Array<String> array = { "A", "B", "C" };

try {
    Clover.println(array[5]);
} catch(Exception e) {
    print("RangeException test...");
    if(e.type() == RangeException) {
        println("TRUE");
    }
    else {
        println("FALSE");
        System.exit(1);
    }
}

