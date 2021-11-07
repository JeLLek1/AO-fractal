void kernel get_color(
	int2 fractalSize,
	double2 ltCorner,
	ulong2 texSize,
	ulong maxLevels,
	double ratio,
	ulong maxColors,
	global uchar* colorTable,
	global uchar* texture){
		size_t y = get_global_id(0);
		double c_im = ratio * y + ltCorner.y;
		for(size_t x = 0; x < fractalSize.x; x++){
			double c_re = ratio * x + ltCorner.x;

			size_t level = 0;
            double z_re = 0, z_im = 0, tmp_re;

			do {
                tmp_re = z_re * z_re - z_im * z_im + c_re;
                z_im = c_im + 2 * z_re * z_im;
                z_re = tmp_re;

                level++;
            } while (z_re * z_re + z_im * z_im < 4 && level < maxLevels);

			size_t arrPos = (y * texSize.x + x) * 3;
			if (level == maxLevels) {
				texture[arrPos] = 0;
				texture[arrPos + 1] = 0;
				texture[arrPos + 2] = 0;
			}else{
				texture[arrPos] = colorTable[(level % maxColors) * 3];
				texture[arrPos + 1] = colorTable[(level % maxColors) * 3 + 1];
				texture[arrPos + 2] = colorTable[(level % maxColors) * 3 + 2];
			}
		}
}
