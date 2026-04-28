#include "system.h"

void readParam(int argc, char** argv, void* paths)
{
    char* e_arg = NULL;
    char* f_arg = NULL;
    char* o_arg = NULL;
    char* q_arg = NULL;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-e") == 0 && i + 1 < argc)
            e_arg = argv[++i];
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc)
            f_arg = argv[++i];
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc)
            o_arg = argv[++i];
        else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc)
            q_arg = argv[++i];
    }

    if (!f_arg)
    {
        fprintf(stderr, "Erro: parametro -f (arquivo .geo) e obrigatorio.\n");
        exit(EXIT_FAILURE);
    }
    if (!o_arg)
    {
        fprintf(stderr, "Erro: parametro -o (diretorio de saida) e obrigatorio.\n");
        exit(EXIT_FAILURE);
    }

    char* bed = strdup(e_arg ? e_arg : "./");
    assert(bed != NULL);
    bed = prepareDir(bed);
    setBed(paths, bed);

    char* bsd = strdup(o_arg);
    assert(bsd != NULL);
    bsd = prepareDir(bsd);
    setBsd(paths, bsd);

    char* geoarq = strdup(f_arg);
    assert(geoarq != NULL);
    setGeoArq(paths, geoarq);

    char* geoname = calloc(MAX_NAME_LEN, sizeof(char));
    assert(geoname != NULL);
    prepareDoc(f_arg, geoname);
    setGeoName(paths, geoname);

    char* bedgeo = calloc(MAX_PATH_LEN, sizeof(char));
    assert(bedgeo != NULL);
    snprintf(bedgeo, MAX_PATH_LEN, "%s%s", bed, f_arg);
    setBedGeo(paths, bedgeo);
    char* bsdgeosvg = calloc(MAX_PATH_LEN, sizeof(char));
    assert(bsdgeosvg != NULL);
    snprintf(bsdgeosvg, MAX_PATH_LEN, "%s%s.svg", bsd, geoname);
    setBsdGeoSvg(paths, bsdgeosvg);

    if (q_arg)
    {
        char* qryarq = strdup(q_arg);
        assert(qryarq != NULL);
        setQryArq(paths, qryarq);

        char* qryname = calloc(MAX_NAME_LEN, sizeof(char));
        assert(qryname != NULL);
        prepareDoc(q_arg, qryname);
        setQryName(paths, qryname);

        char* bedqry = calloc(MAX_PATH_LEN, sizeof(char));
        assert(bedqry != NULL);
        snprintf(bedqry, MAX_PATH_LEN, "%s%s", bed, q_arg);
        setBedQry(paths, bedqry);

        char* bsdgeoqrysvg = calloc(MAX_PATH_LEN, sizeof(char));
        assert(bsdgeoqrysvg != NULL);
        snprintf(bsdgeoqrysvg, MAX_PATH_LEN, "%s%s-%s.svg", bsd, geoname, qryname);
        setBsdGeoQrySvg(paths, bsdgeoqrysvg);
        char* bsdgeoqrytxt = calloc(MAX_PATH_LEN, sizeof(char));
        assert(bsdgeoqrytxt != NULL);
        snprintf(bsdgeoqrytxt, MAX_PATH_LEN, "%s%s-%s.txt", bsd, geoname, qryname);
        setBsdGeoQryTxt(paths, bsdgeoqrytxt);
    }
}
