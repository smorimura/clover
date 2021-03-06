/// logical denial ///

int a = 0;
bool b = false;
bool c = true;
bool d = !c;

println("b --> " + b.toString());
println("c --> " + c.toString());
println("d --> " + d.toString());
println("!!!d --> " + (!!!d).toString());

print("Logical denial Test...");
if(b == false) { // && c == true) { // && d == false) { //&& !!!d == true) {
    println("OK");
}
else {
    println("FALSE");
    System.exit(2);
}

/// complement ///
int e = 11;

println("~11 --> " + (~e).toString());
println("~12 --> " + (~12).toString());

print("Complement Test...");
if(~e == -12 && ~12 == -13) {
    println("OK");
}
else {
    println("FALSE");
    System.exit(2);
}

/// int ///
println("1 + 1 -->" + (1 + 1).toString());
println("1 - 1 -->" + (1 - 1).toString());
println("4 * 3 -->" + (4 * 3).toString());
println("6 / 2 -->" + (6 / 2).toString());
println("6 % 5 -->" + (6 % 5).toString());
println("1 << 3 -->" + (1 << 3).toString());
println("8 >> 2 -->" + (8 >> 2).toString());
println("8 > 2 -->" + (8 > 2).toString());
println("8 < 2 -->" + (8 < 2).toString());

print("int Test1...");
if((1+1) == 2 && (1 -1 ) == 0 && (4 * 3) == 12 && (6/2) == 3 && (6%5) == 1 && (1 << 3) == 8 && (8 >> 2) == 2 && (8 > 2) == true && (8 < 2) == false) 
{
    println("OK");
}
else 
{
    println("FALSE");
    System.exit(2);
}

println("2 >= 2 -->" + (2 >= 2).toString());
println("1 >= 2 -->" + (1 >= 2).toString());
println("3 >= 2 -->" + (3 >= 2).toString());
println("8 <= 2 -->" + (8 <= 2).toString());
println("1 <= 2 -->" + (1 <= 2).toString());
println("2 == 2 -->" + (2 == 2).toString());
println("2 == 3 -->" + (2 == 3).toString());
println("2 != 2 -->" + (2 != 2).toString());
println("2 != 3 -->" + (2 != 3).toString());

print("int Test2...");
if((2>=2) == true && (1>=2) == false && (3>=2) == true && (8<=2) == false && (1<=2) == true && (2==2) == true && (2==3) == false && (2!=2) == false && (2!=3) == true) 
{
    println("OK");
}
else 
{
    println("FALSE");
    System.exit(2);
}

println("1 & 1  -->" + (1 & 1).toString());
println("0 & 1  -->" + (0 & 1).toString());
println("1|2|4  -->" + (1 | 2 | 4).toString());
println("1 ^ 1  -->" + (1 ^ 1).toString());
println("1 ^ 0  -->" + (1 ^ 0).toString());
println("0x0f   -->" + 0x0f.toString());
println("017    -->" + 017.toString());

print("int Test3...");
if((1&1) == 1 && (0 & 1) == 0 && (1|2|4) == 7 && (1^1) == 0 && (1^0) == 1 && 0x0f == 15 && 017 == 15) 
{
    println("OK");
}
else 
{
    println("FALSE");
    System.exit(2);
}

println("true && true -->" + (true && true).toString());
println("false && true -->" + (false && true).toString());
println("false && false -->" + (false && false).toString());
println("true || true -->" + (true || true).toString());
println("false || true -->" + (false || true).toString());
println("false || false -->" + (false || false).toString());
println("true || true -->" + (true || true).toString());

print("logical operator Test...");
if((true && true) == true && (false && true) == false && (false && false) == false && (true || true) == true && (false || true) == true && (false || true) == true && (false || false) == false && (true || true) == true) 
{
    println("OK");
}
else 
{
    println("FALSE");
    System.exit(2);
}

/// float ///
float fvalue1 = 1.1 + 1.2;
println("1.1 + 1.2 -->" + fvalue1.toString());

float an_error_range = fvalue1 - 2.3;

print("float Test1...");
if(an_error_range < 0.1) {
    println("OK");
}
else {
    println("FALSE");
    System.exit(2);
}

fvalue1 = 1.1 * 2.0;
println("1.1 * 2.0 -->" + (1.1 * 2.0).toString());

an_error_range = fvalue1 - 2.2;

print("float Test2...");
if(an_error_range < 0.1) {
    println("OK");
}
else {
    println("FALSE");
    System.exit(2);
}

fvalue1 = 4.4 / 2.0;
println("4.4 / 2.0 -->" + (4.4 / 2.0).toString());

an_error_range = fvalue1 - 2.2;

print("float Test3...");
if(an_error_range < 0.1) {
    println("OK");
}
else {
    println("FALSE");
    System.exit(2);
}

println("8.0 > 2.0 -->" + (8.0 > 2.0).toString());
println("8.0 < 2.0 -->" + (8.0 < 2.0).toString());
println("2.1 >= 2.0 -->" + (2.1 >= 2.0).toString());
println("1.1 >= 2.0 -->" + (1.1 >= 2.0).toString());
println("3.1 >= 2.0 -->" + (3.1 >= 2.0).toString());
println("8.1 <= 2.0 -->" + (8.1 <= 2.0).toString());
println("1.1 <= 2.0 -->" + (1.1 <= 2.0).toString());
println("2.1 == 2.1 -->" + (2.1 == 2.1).toString());
println("2.1 == 3.1 -->" + (2.1 == 3.1).toString());
println("2.1 != 2.1 -->" + (2.1 != 2.1).toString());
println("2.1 != 3.1 -->" + (2.1 != 3.1).toString());

print("float Test4...");
if((8.0 > 2.0) == true && (8.0 < 2.0) == false && (2.1 >= 2.0) == true && (1.1 >= 2.0) == false && (3.1 >= 2.0) == true && (8.1 <= 2.0) == false && (1.1 <= 2.0) == true && (2.1 < 2.1) == false && (2.1 == 3.1) == false && (2.1 != 2.1) == false && (2.1 != 3.1) == true) 
{
    println("OK");
}
else 
{
    println("FALSE");
    System.exit(2);
}

/// substitution ///
int g = 123;
println("g      -->" + g.toString());

print("substitution Test1...");
if(g == 123) {
    println("OK");
}
else 
{
    println("FALSE");
    System.exit(2);
}

g++;
println("g++    -->" + g.toString());

print("substitution Test2...");
if(g == 124) {
    println("OK");
}
else {
    println("FALSE");
    System.exit(2);
}

g+=123;
println("g+=123 -->" + g.toString());

print("substitution Test3...");
if(g == 247) {
    println("OK");
}
else {
    println("FALSE");
    System.exit(2);
}

g-=123;
println("g-=123 -->" + g.toString());

print("substitution Test4...");
if(g == 124) {
    println("OK");
}
else {
    println("FALSE");
    System.exit(2);
}

/// field substitution ///

FieldTest h = new FieldTest();

h.field1 = 123;
println("h.field1               --> " + h.field1.toString());

print("field substitution Test...");
if(h.field1 == 123) {
    println("OK");
}
else {
    println("FALSE");
    System.exit(2);
}

h.field1++;
println("h.field1             --> " + h.field1.toString());

print("field substitution Test2...");
if(h.field1 == 124) {
    println("OK");
}
else {
    println("FALSE");
    System.exit(2);
}

h.field1--;
println("h.field1--             --> " + h.field1.toString());

print("field substitution Test3...");
if(h.field1 == 123) {
    println("OK");
}
else {
    println("FALSE");
    System.exit(2);
}

h.field1 += 123;
println("h.field1+=123          --> " + h.field1.toString());

print("field substitution Test4...");
if(h.field1 == 246) {
    println("OK");
}
else {
    println("FALSE");
    System.exit(2);
}

h.field1 -= 123;
println("h.field1-=123          --> " + h.field1.toString());

print("field substitution Test5...");
if(h.field1 == 123) {
    println("OK");
}
else {
    println("FALSE");
    System.exit(2);
}

FieldTest.static_field = 123;
println("FieldTest.static_field       --> " + FieldTest.static_field.toString());

print("static field substitution Test1...");
if(FieldTest.static_field == 123) {
    println("OK");
}
else {
    println("FALSE");
    System.exit(2);
}

FieldTest.static_field++;
println("FieldTest.static_field++     --> " + FieldTest.static_field.toString());

print("static field substitution Test3...");
if(FieldTest.static_field == 124) {
    println("OK");
}
else {
    println("FALSE");
    System.exit(2);
}

FieldTest.static_field += 123;
println("FieldTest.static_field+=123  --> " + FieldTest.static_field.toString());

print("static field substitution Test4...");
if(FieldTest.static_field == 247) {
    println("OK");
}
else {
    println("FALSE");
    System.exit(2);
}

FieldTest.static_field -= 123;
println("FieldTest.static_field-=123  --> " + FieldTest.static_field.toString());

print("static field substitution Test5...");
if(FieldTest.static_field == 124) {
    println("OK");
}
else {
    println("FALSE");
    System.exit(2);
}

/// comma ///

int i = 1, String j = "aaa", int k = 2;
println("i --> " + i.toString());
println("j --> " + j);
println("k --> " + k.toString());

print("comman test...");
if(i == 1 && j == "aaa" && k == 2) {
    println("OK");
}
else {
    println("FALSE");
    System.exit(2);
}
