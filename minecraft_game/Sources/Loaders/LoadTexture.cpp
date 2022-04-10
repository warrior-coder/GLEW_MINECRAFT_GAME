#include "LoadTexture.hpp"


GLuint c_load_png(const char* fileName, GLuint* width_ptr, GLuint* height_ptr)
{
    FILE* file_ptr;
    fopen_s(&file_ptr, fileName, "rb");
    if (!file_ptr)
    {
        return 0;
    }

    png_byte header[8];
	fread(header, 1, 8, file_ptr);
    GLboolean isPng = !png_sig_cmp(header, 0, 8);
    if (!isPng)
    {
        fclose(file_ptr);
        return 0;
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr)
    {
        fclose(file_ptr);
        return 0;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, (png_infopp)NULL,(png_infopp)NULL);
        fclose(file_ptr);
        return 0;
    }

    png_infop end_info = png_create_info_struct(png_ptr);
    if (!end_info)
    {
        png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
        fclose(file_ptr);
        return 0;
    }

    if (setjmp(png_jmpbuf(png_ptr)))
    {
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(file_ptr);
        return 0;
    }

    png_uint_32 width, height;
    int bit_depth, color_type;
    GLenum alpha;

    png_init_io(png_ptr, file_ptr);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, NULL, NULL, NULL);

	*width_ptr = width;
    *height_ptr = height;

	png_read_update_info(png_ptr, info_ptr);

	png_size_t row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    png_byte* image_data = (png_bytep)malloc(row_bytes * height * sizeof(png_byte));
    if (!image_data)
    {
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(file_ptr);
        return 0;
    }

    png_bytepp row_pointers = (png_bytepp)malloc(height * sizeof(png_bytep));
    if (!row_pointers)
    {
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        free(image_data);
        fclose(file_ptr);
        return 0;
    }

    for (png_size_t i = 0; i < height; i++)
    {
        row_pointers[height - 1 - i] = image_data + i * row_bytes;
    }

    png_read_image(png_ptr, row_pointers);
    switch (png_get_color_type(png_ptr, info_ptr))
	{
	    case PNG_COLOR_TYPE_RGBA:
	        alpha = GL_RGBA;
	    break;
	    case PNG_COLOR_TYPE_RGB:
	        alpha = GL_RGB;
	    break;
	    default:
	        printf("COLOR TYPE %d NOT SUPPORTED\n", png_get_color_type(png_ptr, info_ptr));
	        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	    return 0;
    }

    GLuint texture_id;
    glGenTextures(1, &texture_id); // создаем объект текстуры
    glBindTexture(GL_TEXTURE_2D, texture_id); // привязываем объект текстуры

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // передача 2D текстурных данных в текстуру
    glTexImage2D(
        GL_TEXTURE_2D, // 2D текстура
        0, // уровень маппинга 0
        GL_RGBA, // цветовой формат RGB с прозрачностью
        (GLsizei)width,
        (GLsizei)height,
        0, // без границы
        alpha,
        GL_UNSIGNED_BYTE, // тип каналов 
        (GLvoid*)image_data
    );

    // установка текстурных параметров
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

    // освобождение ресурсов
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    glBindTexture(GL_TEXTURE_2D, 0);
	free(image_data);
    free(row_pointers);
    fclose(file_ptr);

    return texture_id;
}


Texture* LoadTexture(const std::string& fileName)
{
    GLuint width;
	GLuint height;
    GLuint textureId = c_load_png(fileName.c_str(), &width, &height);

    if (!textureId)
    {
        std::cerr << "LOAD_TEXTURE_ERROR: " << fileName << std::endl;
        return nullptr;
    }

	return new Texture(textureId, width, height);
}
