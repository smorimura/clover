class InheritWithBlockTest {
    private int field1;
    private int field2;

    InheritWithBlockTest(int value1, int value2) {
        self.field1 = value1;
        self.field2 = value2;
    }

    void show() with void block {||} {
        Clover.println("self.field1 --> " + self.field1.to_s());

        block();
    }

    inherit void show() with void block {||} {
        inherit();

        Clover.println("self.field2 --> " + self.field2.to_s());
    }
}
