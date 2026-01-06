#include <cstdlib>
#include <string>
#include <cmath>
#include "tgaimage.h"

// 生成桌面路径 C:\Users\xxxx\Desktop\framebuffer.tga
static std::string desktop_path(const char* filename)
{
	// C / C++ 标准库函数，用来读取环境变量（Windows 下 USERPROFILE 通常是 C : \Users\<用户名>）
	const char* home = std::getenv("USERPROFILE");
		if (!home) return filename;
		// std::string：C++ 标准库字符串，用来拼接 \\Desktop\\...
		return std::string(home) + "\\Desktop\\" + filename;
}

// 安全画点，防止越界
// static void ， static 表示只有当前 cpp 可以使用这个函数， void 更准确说：它可能做了事情（产生效果），但不通过 return 某个值 的方式把结果传出来。
static void putpixel(TGAImage& img, int x, int y, const TGAColor& c)
{
	if (x<0 || y<0 || x>img.width() || y>img.height()) return;
	img.set(x, y, c);
}

// 第一版画线： 插值方法
static void drawLine(int x0, int y0, int x1, int y1, TGAImage& img, const TGAColor& c)
{
	int dx = x1 - x0;
	int dy = y1 - y0;
	int steps = std::max(std::abs(dx), std::abs(dy));
	if (steps == 0)
	{
		putpixel(img, x0, y0, c);
		return;
	}
}

int main()
{
	const int width = 256;
	const int height = 256;

	// background color 
	TGAImage img(width, height, TGAImage::RGB, { 0,0,0,255 });

	TGAColor white{ 255,255,255,255 };
	TGAColor red{ 0,0,255,255 };
	TGAColor green{ 0,255,0,255 };
	TGAColor blue{ 255,0,0,255 };

	// draw point
	putpixel(img, 10, 10, white);
	putpixel(img, 50, 20, white);
	putpixel(img, 100, 100, white);

	drawLine(10, 10, 180, 10, img, red);
	drawLine(10, 10, 10, 180, img, green);
	drawLine(10, 10, 180, 180, img, blue);
	drawLine(180, 10, 10, 180, img, white);

	// 输出到桌面
	img.write_tga_file(desktop_path("lesson1.tga"));
	return 0;
}