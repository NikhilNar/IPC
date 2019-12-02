struct message{
    string code;
}

program MAGIC_CODE_PROG{
    version MAGIC_CODE_VERS{
        void sendCode(message)=1;
    }=1;
}=0x23456711;