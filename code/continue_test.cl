int i = 0;
while(i < 5) {
    Clover.println("i ---> " + i.toString());
    if(i == 3) {
        i = 7;
        continue;
    }
    else {
        i++;
    }
}

if(i == 7) {
    Clover.println("continue test1...OK");
}
else {
    Clover.println("continue test1...FALSE");
}

for(int j=0; j<5; j++) {
    if(j == 3) {
        continue;
    }

    Clover.println("j ---> " + j.toString());
}
