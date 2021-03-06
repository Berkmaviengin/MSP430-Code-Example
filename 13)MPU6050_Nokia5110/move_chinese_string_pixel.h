/*------------------------------------------------------------------------------
;  源文件 / 文字 : 欢迎光临本网站！
;  宽×高（像素）: 12×12
;  字模格式/大小 : 单色点阵液晶字模，纵向取模，字节倒序/24字节
;  数据转换日期  : 2004-8-12 14:22:30
------------------------------------------------------------------------------*/
const unsigned char move_chinese_string[][24]=
  {

//对齐方式:左上
//纵向取模 高位在下
//字体:宋体 大小12*12点阵 取模大小12*12点阵 
//字符数8
				//欢

{
0x0a, 0x92, 0x62, 0x9e, 0x02, 0x18, 0x87, 0x74, 0x84, 0x14, 0x0c, 0x00, 0x02, 0x01, 0x00, 0x04, 
0x05, 0x02, 0x01, 0x00, 0x01, 0x02, 0x04, 0x00},

				//迎

{
0x08, 0xf9, 0x02, 0x00, 0xfe, 0x42, 0x41, 0xfe, 0x02, 0x82, 0xfe, 0x00, 0x06, 0x01, 0x02, 0x02, 
0x04, 0x04, 0x04, 0x05, 0x04, 0x04, 0x04, 0x00},

				//光

{
0x10, 0x12, 0x14, 0xf8, 0x10, 0x1f, 0xf0, 0x18, 0x14, 0x12, 0x10, 0x00, 0x04, 0x04, 0x02, 0x01, 
0x00, 0x00, 0x03, 0x04, 0x04, 0x04, 0x07, 0x00},

				//临

{
0xfc, 0x00, 0xff, 0x00, 0x10, 0xcc, 0x47, 0xcc, 0x54, 0x44, 0xc4, 0x00, 0x01, 0x00, 0x07, 0x00, 
0x00, 0x07, 0x02, 0x03, 0x02, 0x02, 0x07, 0x00}, 

				//本

{
0x04, 0x84, 0x44, 0x24, 0x14, 0xff, 0x14, 0x24, 0x44, 0x86, 0x04, 0x00, 0x01, 0x00, 0x01, 0x01, 
0x01, 0x07, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00},



				//网

{
0x00, 0xff, 0x49, 0x31, 0x4d, 0x81, 0x49, 0x31, 0xcd, 0x01, 0xff, 0x00, 0x00, 0x07, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x07, 0x00},

				//站

{
0x04, 0x75, 0x86, 0x74, 0x04, 0xc0, 0x40, 0x7f, 0x44, 0xc4, 0x04, 0x00, 0x02, 0x02, 0x01, 0x01, 
0x01, 0x07, 0x02, 0x02, 0x02, 0x07, 0x00, 0x00},

				//！

{
0x00, 0x1c, 0x7e, 0x7e, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
  };
