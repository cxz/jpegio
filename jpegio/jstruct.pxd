from libcpp.string cimport string
from libcpp.vector cimport vector
from libcpp cimport bool

#from mat2D cimport mat2D

cdef extern from "mat2D.h" namespace "jpegio":
    cdef cppclass mat2D[T]:
        int rows
        int cols
        T* GetBuffer()
    
ctypedef mat2D[int]* ptr_mat2D

cdef extern from "jstruct.h" namespace "jpegio":
    cdef struct struct_huff_tables:
        pass
    #vector[int] counts
    #vector[int] symbols

    cdef struct struct_comp_info:
        pass
    #int component_id
    #int h_samp_factor;
    #int v_samp_factor;
    #int quant_tbl_no;
    #int dc_tbl_no;
    #int ac_tbl_no;

    cdef cppclass jstruct:
        jstruct() except +
        jstruct(string file_path) except +
        jstruct(file_path, load_spatial) except +

        unsigned int image_width
        unsigned int image_height
        int image_components
        unsigned int image_color_space
        int jpeg_components
        unsigned int jpeg_color_space
        unsigned char optimize_coding
        unsigned char progressive_mode

        vector[char *] markers
        vector[ptr_mat2D] coef_arrays
        vector[ptr_mat2D] spatial_arrays
        vector[ptr_mat2D] quant_tables
        vector[struct_huff_tables *] ac_huff_tables
        vector[struct_huff_tables *] dc_huff_tables
        vector[struct_comp_info *] comp_info

        void jpeg_load(string file_path) except +
        void spatial_load(string file_path)
        void jpeg_write(string file_path, bool optimize_coding)
