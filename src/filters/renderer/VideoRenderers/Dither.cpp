/*
 * (C) 2006-2014 see Authors.txt
 *
 * This file is part of WinnerMediaPlayer.
 *
 * WinnerMediaPlayer is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * WinnerMediaPlayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "stdafx.h"
#include "Dither.h"

// Dither matrix in 16-bit floating point format
const unsigned short DITHER_MATRIX[DITHER_MATRIX_SIZE][DITHER_MATRIX_SIZE] = {
	0x2c90, 0x38f4, 0x3bba, 0x29e0, 0x35f4, 0x3230, 0x3bbc, 0x3924, 0x3a46, 0x3644, 0x39e2, 0x370c, 0x3444, 0x3b1a, 0x3140, 0x39d2,
	0x385a, 0x3b24, 0x2c10, 0x38c6, 0x3808, 0x2780, 0x3bbe, 0x37f8, 0x350c, 0x3a6c, 0x3368, 0x3bc0, 0x3000, 0x3886, 0x31b0, 0x3554,
	0x3a94, 0x3618, 0x3430, 0x3a34, 0x3834, 0x39fe, 0x2740, 0x3758, 0x3494, 0x3b7a, 0x2700, 0x3958, 0x3858, 0x3a24, 0x364c, 0x3bc2,
	0x3278, 0x3a22, 0x353c, 0x39de, 0x3268, 0x3a98, 0x36fc, 0x2ed0, 0x39e0, 0x30f0, 0x381a, 0x3996, 0x35ac, 0x3af2, 0x39b8, 0x37bc,
	0x3250, 0x39dc, 0x3800, 0x30e8, 0x3b42, 0x34d4, 0x3970, 0x3afe, 0x3020, 0x3898, 0x33e8, 0x3b34, 0x2e10, 0x3320, 0x391a, 0x26c0,
	0x3784, 0x38de, 0x3060, 0x3b5c, 0x3600, 0x38e6, 0x3490, 0x3b2a, 0x387a, 0x365c, 0x3b3c, 0x2be0, 0x37ac, 0x33d8, 0x2680, 0x3b98,
	0x38d6, 0x2a60, 0x3b7e, 0x391e, 0x36d0, 0x2fe0, 0x3812, 0x32a0, 0x3a84, 0x36b0, 0x3a50, 0x357c, 0x37dc, 0x3b68, 0x3594, 0x3aca,
	0x344c, 0x3a7c, 0x3674, 0x3884, 0x2d30, 0x3a48, 0x3170, 0x398e, 0x2900, 0x3a30, 0x34bc, 0x38ea, 0x3b70, 0x3a3c, 0x3852, 0x3460,
	0x3b04, 0x37a0, 0x351c, 0x2d40, 0x3a80, 0x394e, 0x3b84, 0x3614, 0x3900, 0x2b20, 0x396c, 0x31b8, 0x38ca, 0x3a0c, 0x3038, 0x385c,
	0x39a2, 0x2c70, 0x3ba2, 0x3464, 0x3992, 0x36dc, 0x3bc4, 0x3580, 0x3824, 0x32d0, 0x3abc, 0x2ec0, 0x3560, 0x30f8, 0x3974, 0x3610,
	0x3a12, 0x3110, 0x3aaa, 0x38a2, 0x35e4, 0x341c, 0x28c0, 0x3a02, 0x34a8, 0x3b60, 0x3790, 0x3aa2, 0x2c40, 0x346c, 0x373c, 0x3bc6,
	0x32f0, 0x37e8, 0x391c, 0x3100, 0x3af6, 0x2640, 0x3868, 0x3098, 0x3b3e, 0x3944, 0x3620, 0x3870, 0x39da, 0x374c, 0x3bc8, 0x2e20,
	0x3804, 0x3932, 0x3660, 0x3260, 0x3bca, 0x38ce, 0x3ade, 0x382e, 0x30a0, 0x389e, 0x33a0, 0x363c, 0x3b86, 0x3910, 0x3a58, 0x2820,
	0x36a0, 0x3b28, 0x34e0, 0x3a40, 0x3768, 0x3510, 0x3a54, 0x390e, 0x36e8, 0x2ae0, 0x3bcc, 0x31a0, 0x3aa4, 0x2600, 0x38cc, 0x3400,
	0x3ac4, 0x2800, 0x3b4a, 0x39ee, 0x2cc0, 0x3764, 0x31c8, 0x35cc, 0x3bb6, 0x39a8, 0x2f30, 0x3a1e, 0x3816, 0x3160, 0x35b0, 0x389a,
	0x3a86, 0x3070, 0x3848, 0x2d70, 0x38ba, 0x3baa, 0x2e60, 0x3414, 0x3ae4, 0x3544, 0x3a06, 0x37fc, 0x347c, 0x36d8, 0x3b12, 0x35a4,
	0x3248, 0x3866, 0x34f8, 0x3814, 0x33f8, 0x39c2, 0x3a8a, 0x38e2, 0x25c0, 0x3720, 0x3b26, 0x3508, 0x2980, 0x39b4, 0x3b4c, 0x33a8,
	0x3976, 0x3534, 0x39c4, 0x3b40, 0x3604, 0x31c0, 0x397c, 0x37b0, 0x39d0, 0x3218, 0x38d8, 0x2e30, 0x3b52, 0x39bc, 0x2fa0, 0x3980,
	0x3b9a, 0x39d4, 0x2f40, 0x3960, 0x3b64, 0x3680, 0x2f60, 0x34c8, 0x3acc, 0x3228, 0x3850, 0x395c, 0x3bce, 0x354c, 0x3840, 0x2db0,
	0x37a4, 0x3bd0, 0x2580, 0x33c8, 0x392a, 0x3a82, 0x3530, 0x3b48, 0x2540, 0x3760, 0x3a42, 0x35dc, 0x3890, 0x3308, 0x3844, 0x3710,
	0x3418, 0x366c, 0x3a9a, 0x3590, 0x2500, 0x3888, 0x3bd2, 0x3984, 0x3668, 0x39e4, 0x345c, 0x2d20, 0x371c, 0x3288, 0x3aae, 0x39d6,
	0x31e0, 0x38c8, 0x36e4, 0x3ab2, 0x380c, 0x2b00, 0x389c, 0x3280, 0x392c, 0x3bd4, 0x33b8, 0x3ad6, 0x24c0, 0x3bd6, 0x3a32, 0x2c60,
	0x3b1c, 0x38aa, 0x3238, 0x3902, 0x3ae8, 0x3528, 0x3118, 0x3818, 0x2c50, 0x3ba0, 0x38bc, 0x3ad8, 0x3a20, 0x38f0, 0x2480, 0x36b4,
	0x3b02, 0x34b0, 0x3a00, 0x30a8, 0x3518, 0x3bd8, 0x3688, 0x3a92, 0x34b4, 0x36c0, 0x2f70, 0x3968, 0x3798, 0x3448, 0x35ec, 0x3930,
	0x3750, 0x2a40, 0x3bda, 0x3728, 0x32e8, 0x3a4a, 0x38d2, 0x3b38, 0x33d0, 0x3738, 0x30b8, 0x3628, 0x340c, 0x37d4, 0x3bb2, 0x3428,
	0x3934, 0x2b40, 0x3856, 0x3b0e, 0x3964, 0x31d0, 0x39b0, 0x2e80, 0x38d4, 0x3b1e, 0x3a28, 0x387e, 0x30e0, 0x39a0, 0x3ae2, 0x3208,
	0x3a56, 0x352c, 0x3a14, 0x2d90, 0x3978, 0x3794, 0x2960, 0x35e0, 0x39c6, 0x3a88, 0x3862, 0x3b76, 0x2e40, 0x3988, 0x3128, 0x3a4c,
	0x378c, 0x3b8e, 0x359c, 0x2ea0, 0x36ac, 0x383e, 0x3af8, 0x3404, 0x3780, 0x2a20, 0x3360, 0x3598, 0x3b90, 0x37d0, 0x2dd0, 0x3880,
	0x3358, 0x3946, 0x381c, 0x348c, 0x3b50, 0x3198, 0x3ad4, 0x3940, 0x3050, 0x3540, 0x2440, 0x39cc, 0x3770, 0x3b0a, 0x35d8, 0x386c,
	0x2f00, 0x3380, 0x3a5a, 0x3948, 0x3ba4, 0x2400, 0x35a0, 0x393e, 0x3ba6, 0x39ea, 0x3838, 0x3ab0, 0x27c0, 0x3a38, 0x3538, 0x3bb4,
	0x2380, 0x3b62, 0x30d8, 0x3a62, 0x360c, 0x388c, 0x342c, 0x37e0, 0x3bdc, 0x38f2, 0x3ad0, 0x3488, 0x3168, 0x38da, 0x2300, 0x39ca,
	0x3aee, 0x3630, 0x387c, 0x31a8, 0x34e4, 0x38b8, 0x3a3e, 0x2dc0, 0x3640, 0x3130, 0x34ec, 0x3972, 0x36ec, 0x3318, 0x3950, 0x3714,
	0x3914, 0x356c, 0x38b6, 0x376c, 0x2280, 0x3b9c, 0x39c8, 0x2d50, 0x35e8, 0x32c0, 0x3704, 0x388a, 0x3a64, 0x3558, 0x3bde, 0x3440,
	0x3724, 0x3982, 0x28e0, 0x3ada, 0x375c, 0x3b30, 0x3300, 0x384a, 0x3a74, 0x38e8, 0x3b66, 0x2ee0, 0x385e, 0x3b46, 0x2f90, 0x3ab8,
	0x3178, 0x3a52, 0x2e00, 0x3b08, 0x3918, 0x3150, 0x3678, 0x3aa6, 0x3922, 0x3b14, 0x2fd0, 0x3b8a, 0x2ce0, 0x39a4, 0x379c, 0x2fb0,
	0x3b5a, 0x3240, 0x3a2e, 0x3390, 0x3916, 0x2e90, 0x36c4, 0x3be0, 0x349c, 0x2200, 0x3694, 0x39b2, 0x3478, 0x39f0, 0x35c4, 0x3828,
	0x3be2, 0x36d4, 0x3994, 0x3548, 0x3328, 0x3a04, 0x3854, 0x3498, 0x28a0, 0x3810, 0x39fc, 0x3520, 0x3846, 0x32d8, 0x3ab4, 0x393c,
	0x3864, 0x35b4, 0x380e, 0x3be4, 0x3570, 0x3a96, 0x39ac, 0x3090, 0x3962, 0x37c0, 0x3a9e, 0x3120, 0x3be6, 0x2a00, 0x38f6, 0x3410,
	0x2180, 0x386e, 0x3088, 0x3b82, 0x37a8, 0x3ae6, 0x2f10, 0x3be8, 0x399a, 0x3634, 0x31e8, 0x3912, 0x3b06, 0x36f0, 0x2c30, 0x3504,
	0x3a76, 0x2aa0, 0x39e8, 0x3040, 0x3878, 0x2880, 0x383a, 0x35f8, 0x3aec, 0x32a8, 0x3936, 0x3550, 0x3892, 0x3740, 0x3aea, 0x398c,
	0x3a72, 0x34c4, 0x3a1c, 0x38ac, 0x2860, 0x3584, 0x38fa, 0x372c, 0x3388, 0x3a3a, 0x3b9e, 0x2100, 0x3420, 0x395a, 0x3bae, 0x37d8,
	0x3398, 0x3b6c, 0x3734, 0x34d0, 0x39c0, 0x3b78, 0x3474, 0x3a2c, 0x2b80, 0x3830, 0x3b56, 0x2cb0, 0x3a78, 0x33b0, 0x3018, 0x3650,
	0x30d0, 0x3b20, 0x3690, 0x3350, 0x39ae, 0x3a90, 0x3148, 0x3b44, 0x2cd0, 0x38a0, 0x355c, 0x382a, 0x3a8e, 0x35b8, 0x3190, 0x39ec,
	0x38c4, 0x3068, 0x3938, 0x3b2e, 0x32c8, 0x3748, 0x3008, 0x3894, 0x3bb8, 0x3438, 0x36c8, 0x3904, 0x35fc, 0x396e, 0x3bac, 0x38a6,
	0x397a, 0x37ec, 0x2ca0, 0x3bea, 0x3754, 0x34a4, 0x3836, 0x3956, 0x362c, 0x3b00, 0x30c0, 0x39a6, 0x2fc0, 0x38ae, 0x3abe, 0x2080,
	0x3684, 0x3a70, 0x3568, 0x2000, 0x38c2, 0x3af0, 0x3998, 0x368c, 0x30b0, 0x39ba, 0x3aa8, 0x3200, 0x3b16, 0x2d80, 0x377c, 0x3480,
	0x3b6e, 0x3270, 0x39fa, 0x386a, 0x2ff0, 0x3b10, 0x1f00, 0x3a44, 0x343c, 0x3802, 0x3a66, 0x34b8, 0x3bec, 0x3708, 0x3340, 0x3882,
	0x3bee, 0x3298, 0x3806, 0x3a08, 0x3638, 0x2d00, 0x34ac, 0x3a60, 0x38ee, 0x35c8, 0x29c0, 0x380a, 0x34f0, 0x38f8, 0x3aac, 0x1e00,
	0x3564, 0x38fe, 0x3468, 0x3ace, 0x35d0, 0x394a, 0x37b4, 0x31f8, 0x3bf0, 0x2bc0, 0x38d0, 0x36b8, 0x2940, 0x3926, 0x3b32, 0x35a8,
	0x2d60, 0x38e0, 0x3b58, 0x3078, 0x3a9c, 0x37e4, 0x3bf2, 0x2e50, 0x33f0, 0x3b72, 0x38b4, 0x39e6, 0x3bf4, 0x3290, 0x3670, 0x3a1a,
	0x3842, 0x3a68, 0x2920, 0x37c4, 0x32b8, 0x3b88, 0x34c0, 0x396a, 0x3664, 0x39b6, 0x3330, 0x3b5e, 0x39ce, 0x3484, 0x3080, 0x39aa,
	0x3a4e, 0x3700, 0x34e8, 0x395e, 0x3310, 0x3908, 0x3588, 0x384e, 0x3ac6, 0x3730, 0x3220, 0x3574, 0x2de0, 0x37f0, 0x399c, 0x2ef0,
	0x3188, 0x369c, 0x3bf6, 0x390a, 0x39f2, 0x2b60, 0x3872, 0x3aa0, 0x2df0, 0x3b0c, 0x37cc, 0x2da0, 0x382c, 0x3ae0, 0x38b0, 0x3788,
	0x33c0, 0x3afa, 0x2ba0, 0x3826, 0x3b6a, 0x1d00, 0x39f8, 0x3108, 0x3920, 0x1c00, 0x3a26, 0x3b22, 0x38ec, 0x3ac2, 0x3458, 0x3b7c,
	0x3a8c, 0x38a8, 0x34d8, 0x3048, 0x3654, 0x3adc, 0x3138, 0x3744, 0x3450, 0x38be, 0x34f4, 0x3a10, 0x3210, 0x35bc, 0x2840, 0x3b92,
	0x3058, 0x3986, 0x3698, 0x39d8, 0x3434, 0x36f8, 0x3b18, 0x3524, 0x3a7a, 0x35d4, 0x3822, 0x3408, 0x36bc, 0x2ac0, 0x3896, 0x3624,
	0x1a00, 0x3378, 0x3a16, 0x3b3a, 0x381e, 0x3338, 0x3906, 0x39f6, 0x3bf8, 0x3158, 0x3ad2, 0x36e0, 0x3bfa, 0x392e, 0x3a5c, 0x3648,
	0x38dc, 0x34cc, 0x3bfc, 0x30c8, 0x3ab6, 0x3942, 0x32b0, 0x38a4, 0x2d10, 0x3b96, 0x394c, 0x2f80, 0x3bfe, 0x3966, 0x3258, 0x39be,
	0x3bb0, 0x3928, 0x361c, 0x2c00, 0x3990, 0x3b8c, 0x3578, 0x2a80, 0x36cc, 0x3952, 0x1800, 0x388e, 0x33e0, 0x2f20, 0x384c, 0x31d8,
	0x3a18, 0x1400, 0x3876, 0x358c, 0x383c, 0x2c20, 0x3b80, 0x3774, 0x3a36, 0x3470, 0x31f0, 0x3a0a, 0x3832, 0x3514, 0x3a6a, 0x37f4,
	0x367c, 0x3028, 0x3ac8, 0x37b8, 0x34a0, 0x2f50, 0x3a5e, 0x3874, 0x3b36, 0x34fc, 0x3a6e, 0x35f0, 0x399e, 0x3aba, 0x3500, 0x3b74,
	0x37c8, 0x3ac0, 0x398a, 0x3010, 0x3a7e, 0x3658, 0x38e4, 0x3030, 0x3608, 0x3860, 0x3af4, 0x3718, 0x29a0, 0x3b2c, 0x2eb0, 0x3424,
	0x3a0e, 0x3820, 0x32f8, 0x3954, 0x3afc, 0x38c0, 0x36a4, 0x3370, 0x2e70, 0x38b2, 0x3180, 0x3ba8, 0x2c80, 0x3778, 0x390c, 0x2cf0,
	0x35c0, 0x32e0, 0x36f4, 0x3b94, 0x3454, 0x39f4, 0x3348, 0x397e, 0x3b4e, 0x0000, 0x38fc, 0x34dc, 0x3a2a, 0x36a8, 0x393a, 0x3b54,
};
