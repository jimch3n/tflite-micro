#ifndef FRONTENDPARAMS_H
#define FRONTENDPARAMS_H
/* Create Configuration */
typedef struct {
    AScalar  FrameSizeMs;                 /*  The number of samples to step in minisecond. */
    AScalar  WindowSizeMs;                /* The window length in samples in minisecond.  */
    uint16_t WindowType;                  /* WIN_HANN = 1, WIN_HAMMING =2 */
    AScalar  MelLowFreq;                  /* Lower bound on the frequencies to be included in the mel spectrum. sample rate = 16KHz*/
    AScalar  MelHiFreq;                   /* The desired top edge of the highest frequency band.  */
    uint16_t MelBands;                    /*How many bands in the resulting mel spectrum.  */
    uint16_t Mfcc;                        /* number of MFCC  */
    AScalar  LogMelOffset;                /* LOG_MEL offset */
    AScalar  LogMelClipMin;               /* LOG_MEL clip min */
    uint16_t FeatureType;                 /* LOG_MEL_SPEC = 1, MFCC = 2 */
    AScalar  QuantizationParamScale;      /* output int8_t quantization parameter scale, zero-point */
    AScalar  QuantizationParamZeroPoint;  /* output int8_t quantization parameter scale, zero-point */
} frontend_config_t;

#endif  /* FRONTENDPARAMS_H */
