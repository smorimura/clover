
class Base {
    int field1;

    Base() {}

    void show() {
        Clover.println("field1 " + self.field1.to_s());
    }
    void method() {
        Clover.println("I'm Base.method().");
    }
    void method2() {
        Clover.println("I'm Base.method2().");
    }
}

class Extended extends Base {
    int field2;

    Extended(int a, int b) {
        self.field1 = a;
        self.field2 = b;
    }

    void show() {
        super();
        Clover.println("field2 " + self.field2.to_s());
    }

    void method2() {
        Clover.println("I'm Extended. method2().");
    }
}

inherit class Base {
    inherit void show() {
        inherit();
        Clover.println("X field1 " + self.field1.to_s());
    }
    void method3() {
        Clover.println("I'm Base.method3().");
    }
}

