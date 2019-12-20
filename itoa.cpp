实现字符串转数字 类似std::stoi int stoi (const string&  str, size_t* idx = 0, int base = 10);
str
  String object with the representation of an integral number.
idx
  Pointer to an object of type size_t, whose value is set by the function to position of the next character in str after the numerical value.
  This parameter can also be a null pointer, in which case it is not used.
base
  Numerical base (radix) that determines the valid characters and their interpretation.
  If this is 0, the base used is determined by the format in the sequence (see strtol for details). 
  Notice that by default this argument is 10, not 0.
  
  void itoa(int val, char *buff, int base)
  {
        const char bitchar[] = "0123456789abcdef";
        unsigned uval;

        int index(0);
        if(val==0) {
            buff[0] = '0';
            buff[1] = '\0';
            return;
        }

        int sign(1);
        if(base==10 && val<0) {
            uval = (unsigned)-val;   // 避免最小负数取反后溢出
            sign = -1;
            buff[index++] = '-';
        }
        else uval = (unsigned)val;

        // 逆序存储
        while(uval)
        {
            int v = uval % base;
            buff[index++] = bitchar[v];
            uval /= base;
        }

        int k(0), i(index-1);
        if(sign==-1) k = 1;

        // 反转除符号位外其他位
        while(k<i)
        {
            char temp = buff[k];
            buff[k] = buff[i];
            buff[i] = temp;
            i--; k++;
        }

        // 字符串以'\0' 结尾，注意不能写为'0'，这将代表字符0.
        buff[index] = '\0';
    }
