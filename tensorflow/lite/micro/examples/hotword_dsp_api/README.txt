@ this example is demostration hotword dsp api release from 07/11/2024 (642444186)

normal hotword processing

1. hotword_dsp_api links wb config lib, tflite micro lib, speech micro lib.
2. use normal large y google model
3. run cycle count get  32860295 frame count:185

optimize hotword processing

1. convert model (WB) from tflite -> SVDF, FC, operator remapping to IA8201 HMD MVM permuatation
2. replace kernel with MVM optimization svdf, fc, signal processing objects ( energy.o filter_bank.o filter_bank_spectral_subtraction.o  window.o filter_bank_log.o)
3. create new tflite micro lib call "libtensorflow-microlite-kn.a"
4. run total cycle count get 14194759 frame count:185



