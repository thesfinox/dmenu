static int
issel(size_t id)
{
	for (int i = 0;i < selidsize;i++)
		if (selid[i] == id)
			return 1;
	return 0;
}

static void
printsel(unsigned int state)
{
	for (int i = 0;i < selidsize;i++)
		if (selid[i] != -1 && (!sel || sel->id != selid[i])) {
			if (enabled(PrintIndex))
				printf("%d\n", selid[i]);
			else
				puts(items[selid[i]].text);
		}
	if (sel && !(state & ShiftMask)) {
		if (enabled(PrintIndex))
			printf("%d\n", sel->index);
		else
			puts(sel->text);
	} else
		puts(text);
}

static void
selsel()
{
	if (!sel)
		return;
	if (issel(sel->id)) {
		for (int i = 0; i < selidsize; i++)
			if (selid[i] == sel->id)
				selid[i] = -1;
	} else {
		for (int i = 0; i < selidsize; i++)
			if (selid[i] == -1) {
				selid[i] = sel->id;
				return;
			}
		selidsize++;
		selid = realloc(selid, (selidsize + 1) * sizeof(int));
		selid[selidsize - 1] = sel->id;
	}
}