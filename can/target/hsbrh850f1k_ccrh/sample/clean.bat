@echo off
rem #
rem #  TOPPERS/A-RTEGEN
rem #      Automotive Runtime Environment Generator
rem #
rem #  Copyright (C) 2014-2015 by FUJI SOFT INCORPORATED, JAPAN
rem #
rem #  ��L���쌠�҂́C�ȉ���(1)�`(4)�̏����𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F
rem #  �A�i�{�\�t�g�E�F�A�����ς������̂��܂ށD�ȉ������j���g�p�E�����E��
rem #  �ρE�Ĕz�z�i�ȉ��C���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
rem #  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
rem #      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
rem #      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
rem #  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
rem #      �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
rem #      �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
rem #      �̖��ۏ؋K����f�ڂ��邱�ƁD
rem #  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
rem #      �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂�����
rem #      �ƁD
rem #    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
rem #        �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
rem #    (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g��
rem #        �񍐂��邱�ƁD
rem #  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
rem #      �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
rem #      �܂��C�{�\�t�g�E�F�A�̃��[�U�܂��̓G���h���[�U����̂����Ȃ闝
rem #      �R�Ɋ�Â�����������C��L���쌠�҂����TOPPERS�v���W�F�N�g��
rem #      �Ɛӂ��邱�ƁD
rem #
rem #  �{�\�t�g�E�F�A�́CAUTOSAR�iAUTomotive Open System ARchitecture�j�d
rem #  �l�Ɋ�Â��Ă���D��L�̋����́CAUTOSAR�̒m�I���Y��������������̂�
rem #  �͂Ȃ��DAUTOSAR�́CAUTOSAR�d�l�Ɋ�Â����\�t�g�E�F�A�����p�ړI�ŗ�
rem #  �p����҂ɑ΂��āCAUTOSAR�p�[�g�i�[�ɂȂ邱�Ƃ����߂Ă���D
rem #
rem #  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
rem #  ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC����̎g�p�ړI
rem #  �ɑ΂���K�������܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F
rem #  �A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C��
rem #  �̐ӔC�𕉂�Ȃ��D
rem #
rem #  $Id: hsbv850e2fg4_cx_common.yaml 470 2014-10-10 05:33:29Z ksigihar $
rem #

del /F Can_* cfg1_out.*
del /F atk2-sc1.mtpj *.mtud
rmdir /S /Q cancfg cfg kernel DefaultBuild

@pause
exit
