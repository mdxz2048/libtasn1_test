# 在Ubuntu系统下安装测试Libtasn1

## 介绍

[官方手册](https://www.gnu.org/software/libtasn1/manual/libtasn1.html)

## 安装

1. 下载并解压

   ```sh
   wget ftp://ftp.gnu.org/gnu/libtasn1/libtasn1-4.18.0.tar.gz
   tar -xvf libtasn1-4.18.0.tar.gz
   ```

   

2. 执行如下指令，编译`libtasn1`; 

   ```
   ./configure --prefix=/usr --disable-static && make
   ```

   

3. 检查安装结果

   ```
   make check
   ```

   - 通过安装效果

     ```sh
     ============================================================================
     Testsuite summary for GNU Libtasn1 4.18.0
     ============================================================================
     # TOTAL: 30
     # PASS:  30
     # SKIP:  0
     # XFAIL: 0
     # FAIL:  0
     # XPASS: 0
     # ERROR: 0
     ============================================================================
     
     ```

     

   - 如果安装未通过，执行如下指令：

     ```sh
     make -C doc/reference install-data-local
     ```

     

4. 切换到`root`用户，安装：

   ```SH
   make install
   ```

   

5. 安装完成，可以在shell看到如下几个程序:

   ```sh
   root@ubuntu:/home/caeri/lzp/GIT/libtasn1-4.18.0# asn1
   asn1c         asn1Coding    asn1Decoding  asn1Parser
   ```

   

## 测试

### Encode编码

1. 新建一个名称为**pkix.asn**的文件，文件中我们定义了两个数据类型`Dss-Sig-Value`和`OtherStruct`。内容如下:

   ```ASN.1
   MYPKIX1 { }
   
   DEFINITIONS IMPLICIT TAGS ::=
   
   BEGIN
   
   OtherStruct ::= SEQUENCE {
        x       INTEGER,
        y       CHOICE {
            y1 INTEGER,
            y2 OCTET STRING }
   }
   
   Dss-Sig-Value ::= SEQUENCE {
        r       INTEGER,
        s       INTEGER,
        other   OtherStruct,
        z       INTEGER OPTIONAL
   }
   
   END
   ```

   

2. 新建名称为 **assign.asn1的**文件，新建一个`Dss-Sig-Value`的实例`dp`，并赋值。内容如下:

   ```ASN.1
   dp MYPKIX1.Dss-Sig-Value
   
   r 42
   s 47
   other.x 66
   other.y y1
   other.y.y1 15
   z (NULL)
   ```

   

3. 执行如下指令,进行编码测试:

   ```sh
   asn1Coding pkix.asn assign.asn1
   ```

   

4. 可以看到输出结果如下:

   ```sh
   Parse: done.
   
   var=dp, value=MYPKIX1.Dss-Sig-Value
   var=r, value=42
   var=s, value=47
   var=other.x, value=66
   var=other.y, value=y1
   var=other.y.y1, value=15
   var=z, value=(NULL)
   
   name:NULL  type:SEQUENCE
     name:r  type:INTEGER  value:0x2a
     name:s  type:INTEGER  value:0x2f
     name:other  type:SEQUENCE
       name:x  type:INTEGER  value:0x42
       name:y  type:CHOICE
         name:y1  type:INTEGER  value:0x0f
   
   Coding: SUCCESS
   
   -----------------
   Number of bytes=16
   30 0e 02 01 2a 02 01 2f 30 06 02 01 42 02 01 0f 
   -----------------
   
   OutputFile=assign.out
   
   Writing: done.
   ```

   

5. 同时会生产DER编码的文件**assign.out**，可以查看文件内容如下:

   ```sh
   hexdump -x assign.out
   0000000    0e30    0102    022a    2f01    0630    0102    0242    0f01
   0000010
   ```

   

### Decode解码

1. 这里我们在上边Encode编码的基础上，利用**pkix.asn**、**assign.out**,执行如下指令:

   ```sh
   asn1Decoding pkix.asn assign.out MYPKIX1.Dss-Sig-Value
   ```

2. 可以看到解析结果如下:

   ```sh
   Parse: done.
   
   Decoding: SUCCESS
   
   DECODING RESULT:
   name:NULL  type:SEQUENCE
     name:r  type:INTEGER  value:0x2a
     name:s  type:INTEGER  value:0x2f
     name:other  type:SEQUENCE
       name:x  type:INTEGER  value:0x42
       name:y  type:CHOICE
         name:y1  type:INTEGER  value:0x0f
   ```

