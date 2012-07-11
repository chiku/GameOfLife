#ifndef GOL_INTERFACE_BASE_GRAPHICS_H
#define GOL_INTERFACE_BASE_GRAPHICS_H

typedef struct Graphics Graphics;

Graphics* Graphics_Initialize();
void Graphics_Destroy(Graphics *self);
void Graphics_Cleanup_On_Signal(Graphics *self);

void Graphics_Callback_Handler(Graphics *self, double time_in_s);

void Graphics_Draw_At(Graphics *self, long int x, long int y);
void Graphics_Flush(Graphics *self);
void Graphics_Set_Draw_Color(Graphics *self);
void Graphics_Set_Erase_Color(Graphics *self);

#endif
