#include <sys/types.h>
#include <blf.h>
#include <string.h>

int
main(void)
{
	blf_ctx c;
	char    key[] = "AAAAA";
	char    key2[] = "abcdefghijklmnopqrstuvwxyz";

	u_int32_t data[10];
	u_int32_t data2[] =
	{0x424c4f57l, 0x46495348l};

	u_int16_t i;

	/* First test */
	for (i = 0; i < 10; i++)
		data[i] = i;

	blf_key(&c, (u_int8_t *) key, 5);
	blf_enc(&c, data, 5);
	{
		u_int32_t *d;
		u_int16_t i;

		d = data;
		for (i = 0; i < 5; i++) {
			Blowfish_encipher(&c, d, d + 1);
			d += 2;
		}
	}


	blf_dec(&c, data, 1);
	blf_dec(&c, data + 2, 4);


	blf_enc(&c, data2, 1);
	blf_dec(&c, data2, 1);
	return 0;
}
