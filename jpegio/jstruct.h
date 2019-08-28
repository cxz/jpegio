    #ifndef JSTRUCT_H_
#define JSTRUCT_H_

#include <vector>
#include "mat2D.h"
extern "C"
{
#include "jpeglib.h"
#include "jmorecfg.h"
}

struct struct_huff_tables {
	std::vector<int> counts; 
	std::vector<int> symbols;
};
struct struct_comp_info {
	int component_id;
	int h_samp_factor;
	int v_samp_factor;
	int quant_tbl_no;
	int dc_tbl_no;
	int ac_tbl_no;
    JDIMENSION downsampled_height;
    JDIMENSION downsampled_width;
    JDIMENSION height_in_blocks;
    JDIMENSION width_in_blocks;
};

namespace jpegio {

    class jstruct
    {
    public:
        unsigned int image_width;
        unsigned int image_height;
        int image_components;
        unsigned int image_color_space;
        int jpeg_components;
        std::vector<char *> markers;
        unsigned int jpeg_color_space;
        std::vector<mat2D<int> *> coef_arrays;
        std::vector<mat2D<int> *> spatial_arrays;
        std::vector<mat2D<int> *> quant_tables;
        std::vector<struct_huff_tables *> ac_huff_tables;
        std::vector<struct_huff_tables *> dc_huff_tables;
        unsigned char optimize_coding;
        std::vector<struct_comp_info *> comp_info;
        unsigned char progressive_mode;

        jstruct() {}
        jstruct(std::string file_path);
        jstruct(std::string file_path, bool load_spatial);
        ~jstruct();

        void jpeg_write(std::string file_path, bool optimize_coding);
        void jpeg_load(std::string file_path);
        void spatial_load(std::string file_path);

    private:
        bool load_spatial;
    };

}
#endif
