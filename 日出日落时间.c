#include <stdio.h>
#include <math.h>
#include <time.h>

#define QW 3.1415926

double f1(double a1, double a2, double a3)
{
	double b1, b2;
	b1 = 0;
	if (a1 > 1582 || (a1 == 1582 && (a2 > 10 || (a2 == 10 && a3 > 14))))
		b1 = 2 - floor(a1 / 100.0) + floor((a1 / 100.0) / 4);
	if (a2 == 1 || a2 == 2) {
		a1 = a1 - 1;
		a2 = a2 + 12;
	}
	b2 = floor(365.25 * (a1 + 4716)) + floor(30.6001 * (a2 + 1)) + a3 + b1 - 1524.5;
	return b2;
}

double f2(double a)
{
	double b, c, d, e, f;

	b = 23.0 + (26.0 + ((21.448 - a * (46.8150 + a * (0.00059 - a * (0.001813)))) / 60.0)) / 60.0
		+ 0.00256 * cos((125.04 - 1934.136 * a) * (QW / 180.0));

	c = 280.46646 + a * (36000.76983 + a * (0.0003032));
	while (c > 360.0) c -= 360.0;
	while (c < 0.0) c += 360.0;

	d = 0.016708634 - a * (0.000042037 + 0.0000001267 * a);
	e = 357.52911 + a * (35999.05029 - 0.0001537 * a);
	f = tan(b * (QW / 180.0) / 2.0) * tan(b * (QW / 180.0) / 2.0);

	return (f * sin(2.0 * c * (QW / 180.0))
		- 2.0 * d * sin(e * (QW / 180.0))
		+ 4.0 * d * f * sin(e * (QW / 180.0)) * cos(2.0 * c * (QW / 180.0))
		- 0.5 * f * f * sin(4.0 * c * (QW / 180.0))
		- 1.25 * d * d * sin(2.0 * e * (QW / 180.0))) * (180.0 / QW) * 4.0;
}

double f3(double a, double b, double c)
{
	double d, e, f, g, h;

	d = ((a - b / 360.0) - 2451545.0) / 36525.0;
	e = f2(d);
	f = 720.0 - (b * 4) - e;
	g = ((a - 0.5 + f / 1440.0) - 2451545.0) / 36525.0;
	e = f2(g);
	h = 720 - (b * 4) - e + (c * 60.0);

	while (h < 0.0) h += 1440.0;
	while (h >= 1440.0) h -= 1440.0;

	return h;
}

double f4(int a, double b, double c, double d)
{
	double e, f, g, h, i, j, k, l, m, n, o, p;

	e = (b - 2451545.0) / 36525.0;
	f = f2(e);

	j = 23.0 + (26.0 + ((21.448 - e * (46.8150 + e * (0.00059 - e * (0.001813)))) / 60.0)) / 60.0
		+ 0.00256 * cos((125.04 - 1934.136 * e) * (QW / 180.0));

	k = 280.46646 + e * (36000.76983 + e * (0.0003032));
	while (k > 360.0) k -= 360.0;
	while (k < 0.0) k += 360.0;

	l = 357.52911 + e * (35999.05029 - 0.0001537 * e);
	m = 125.04 - 1934.136 * e;

	n = k + sin(l * (QW / 180.0)) * (1.914602 - e * (0.004817 + 0.000014 * e))
		+ sin(2 * l * (QW / 180.0)) * (0.019993 - 0.000101 * e)
		+ sin(3 * l * (QW / 180.0)) * 0.000289
		- 0.00569 - 0.00478 * sin(m * (QW / 180.0));

	o = (asin(sin(j * (QW / 180.0)) * sin(n * (QW / 180.0)))) * (180.0 / QW);

	p = c * (QW / 180.0);
	i = o * (QW / 180.0);
	h = acos(cos(90.833 * (QW / 180.0)) / (cos(p) * cos(i)) - tan(p) * tan(i));

	if (!a) h = -h;

	g = d + h * (180.0 / QW);
	return 720 - (4.0 * g) - f;
}

double f5(int a, double b, double c, double d, double e)
{
	double f, g, h, i, j;

	f = f4(a, b, c, d);
	g = f4(a, b + f / 1440.0, c, d);
	h = g + (e * 60.0);

	if ((h < 0.0) || (h >= 1440.0)) {
		double k;
		k = ((h < 0) ? 1 : -1);
		while ((h < 0.0) || (h >= 1440.0)) {
			h += k * 1440.0;
			i -= k;
		}
	}

	return h;
}

void f6(char a[], double b, int c)
{
	double d, e, f;

	d = floor(b / 60.0);
	e = floor(60.0 * (b / 60.0 - floor(b / 60.0)));
	f = floor(60.0 * (60.0 * (b / 60.0 - floor(b / 60.0)) - floor(60.0 * (b / 60.0 - floor(b / 60.0)))) + 0.5);

	if (f > 59) {
		f = 0;
		e += 1;
	}
	if ((c == 2) && (f >= 30)) e++;
	if (e > 59) {
		e = 0;
		d += 1;
	}

	if (c > 2)
		sprintf(a, "%02d:%02d:%02d", (int)d, (int)e, (int)f);
	else
		sprintf(a, "%02d:%02d", (int)d, (int)e);
}

void f7(void)
{
	double a, b, c, d;
	char e[1000];
	int f = 2022, g = 8, h = 15;
	double i = 34.035672, j = 108.760064;
	double k = 8.0;

	scanf("%d%d%d", &f, &g, &h);
	scanf("%lf%lf", &j, &i);
	scanf("%lf", &k);

	a = f1(f, g, h);
	b = f3(a, j, k);
	f6(e, b, 3);
	printf("Solar Noon=%s\n", e);

	c = f5(1, a, i, j, k);
	f6(e, c, 3);
	printf("   Sunrise=%s\n", e);

	d = f5(0, a, i, j, k);
	f6(e, d, 3);
	printf("    Sunset=%s", e);
}

int main()
{
	f7();
	return 0;
}
