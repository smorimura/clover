
FieldInitializer a = new FieldInitializer();

print("field initializer test2...");
if(a.get_field() == 123 && a.get_field2() == "AAA" && a.get_field3() == 0 && a.get_field4() == null) 
{
    println("OK");
}
else {
    println("FALSE");
    System.exit(1);
}
