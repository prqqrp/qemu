/*
 *  Test program for MSA instruction ADDV.B
 *
 *  Copyright (C) 2019  Wave Computing, Inc.
 *  Copyright (C) 2019  Aleksandar Markovic <amarkovic@wavecomp.com>
 *  Copyright (C) 2019  RT-RK Computer Based Systems LLC
 *  Copyright (C) 2019  Mateja Marjanovic <mateja.marjanovic@rt-rk.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <sys/time.h>
#include <stdint.h>

#include "../../../../include/wrappers_msa.h"
#include "../../../../include/test_inputs_128.h"
#include "../../../../include/test_utils_128.h"

#define TEST_COUNT_TOTAL (                                                \
            (PATTERN_INPUTS_SHORT_COUNT) * (PATTERN_INPUTS_SHORT_COUNT) + \
            (RANDOM_INPUTS_SHORT_COUNT) * (RANDOM_INPUTS_SHORT_COUNT))


int32_t main(void)
{
    char *instruction_name = "ADDV.B";
    int32_t ret;
    uint32_t i, j;
    struct timeval start, end;
    double elapsed_time;

    uint64_t b128_result[TEST_COUNT_TOTAL][2];
    uint64_t b128_expect[TEST_COUNT_TOTAL][2] = {
        { 0xfefefefefefefefeULL, 0xfefefefefefefefeULL, },    /*   0  */
        { 0xffffffffffffffffULL, 0xffffffffffffffffULL, },
        { 0xa9a9a9a9a9a9a9a9ULL, 0xa9a9a9a9a9a9a9a9ULL, },
        { 0x5454545454545454ULL, 0x5454545454545454ULL, },
        { 0xcbcbcbcbcbcbcbcbULL, 0xcbcbcbcbcbcbcbcbULL, },
        { 0x3232323232323232ULL, 0x3232323232323232ULL, },
        { 0xe28d37e28d37e28dULL, 0x37e28d37e28d37e2ULL, },
        { 0x1b70c61b70c61b70ULL, 0xc61b70c61b70c61bULL, },
        { 0xffffffffffffffffULL, 0xffffffffffffffffULL, },    /*   8  */
        { 0x0000000000000000ULL, 0x0000000000000000ULL, },
        { 0xaaaaaaaaaaaaaaaaULL, 0xaaaaaaaaaaaaaaaaULL, },
        { 0x5555555555555555ULL, 0x5555555555555555ULL, },
        { 0xccccccccccccccccULL, 0xccccccccccccccccULL, },
        { 0x3333333333333333ULL, 0x3333333333333333ULL, },
        { 0xe38e38e38e38e38eULL, 0x38e38e38e38e38e3ULL, },
        { 0x1c71c71c71c71c71ULL, 0xc71c71c71c71c71cULL, },
        { 0xa9a9a9a9a9a9a9a9ULL, 0xa9a9a9a9a9a9a9a9ULL, },    /*  16  */
        { 0xaaaaaaaaaaaaaaaaULL, 0xaaaaaaaaaaaaaaaaULL, },
        { 0x5454545454545454ULL, 0x5454545454545454ULL, },
        { 0xffffffffffffffffULL, 0xffffffffffffffffULL, },
        { 0x7676767676767676ULL, 0x7676767676767676ULL, },
        { 0xddddddddddddddddULL, 0xddddddddddddddddULL, },
        { 0x8d38e28d38e28d38ULL, 0xe28d38e28d38e28dULL, },
        { 0xc61b71c61b71c61bULL, 0x71c61b71c61b71c6ULL, },
        { 0x5454545454545454ULL, 0x5454545454545454ULL, },    /*  24  */
        { 0x5555555555555555ULL, 0x5555555555555555ULL, },
        { 0xffffffffffffffffULL, 0xffffffffffffffffULL, },
        { 0xaaaaaaaaaaaaaaaaULL, 0xaaaaaaaaaaaaaaaaULL, },
        { 0x2121212121212121ULL, 0x2121212121212121ULL, },
        { 0x8888888888888888ULL, 0x8888888888888888ULL, },
        { 0x38e38d38e38d38e3ULL, 0x8d38e38d38e38d38ULL, },
        { 0x71c61c71c61c71c6ULL, 0x1c71c61c71c61c71ULL, },
        { 0xcbcbcbcbcbcbcbcbULL, 0xcbcbcbcbcbcbcbcbULL, },    /*  32  */
        { 0xccccccccccccccccULL, 0xccccccccccccccccULL, },
        { 0x7676767676767676ULL, 0x7676767676767676ULL, },
        { 0x2121212121212121ULL, 0x2121212121212121ULL, },
        { 0x9898989898989898ULL, 0x9898989898989898ULL, },
        { 0xffffffffffffffffULL, 0xffffffffffffffffULL, },
        { 0xaf5a04af5a04af5aULL, 0x04af5a04af5a04afULL, },
        { 0xe83d93e83d93e83dULL, 0x93e83d93e83d93e8ULL, },
        { 0x3232323232323232ULL, 0x3232323232323232ULL, },    /*  40  */
        { 0x3333333333333333ULL, 0x3333333333333333ULL, },
        { 0xddddddddddddddddULL, 0xddddddddddddddddULL, },
        { 0x8888888888888888ULL, 0x8888888888888888ULL, },
        { 0xffffffffffffffffULL, 0xffffffffffffffffULL, },
        { 0x6666666666666666ULL, 0x6666666666666666ULL, },
        { 0x16c16b16c16b16c1ULL, 0x6b16c16b16c16b16ULL, },
        { 0x4fa4fa4fa4fa4fa4ULL, 0xfa4fa4fa4fa4fa4fULL, },
        { 0xe28d37e28d37e28dULL, 0x37e28d37e28d37e2ULL, },    /*  48  */
        { 0xe38e38e38e38e38eULL, 0x38e38e38e38e38e3ULL, },
        { 0x8d38e28d38e28d38ULL, 0xe28d38e28d38e28dULL, },
        { 0x38e38d38e38d38e3ULL, 0x8d38e38d38e38d38ULL, },
        { 0xaf5a04af5a04af5aULL, 0x04af5a04af5a04afULL, },
        { 0x16c16b16c16b16c1ULL, 0x6b16c16b16c16b16ULL, },
        { 0xc61c70c61c70c61cULL, 0x70c61c70c61c70c6ULL, },
        { 0xffffffffffffffffULL, 0xffffffffffffffffULL, },
        { 0x1b70c61b70c61b70ULL, 0xc61b70c61b70c61bULL, },    /*  56  */
        { 0x1c71c71c71c71c71ULL, 0xc71c71c71c71c71cULL, },
        { 0xc61b71c61b71c61bULL, 0x71c61b71c61b71c6ULL, },
        { 0x71c61c71c61c71c6ULL, 0x1c71c61c71c61c71ULL, },
        { 0xe83d93e83d93e83dULL, 0x93e83d93e83d93e8ULL, },
        { 0x4fa4fa4fa4fa4fa4ULL, 0xfa4fa4fa4fa4fa4fULL, },
        { 0xffffffffffffffffULL, 0xffffffffffffffffULL, },
        { 0x38e28e38e28e38e2ULL, 0x8e38e28e38e28e38ULL, },
        { 0x10d4cc9850c4aa80ULL, 0x96ce16bcfcf66018ULL, },    /*  64  */
        { 0x8328e62f75f51c48ULL, 0x5d5ec67813ba0208ULL, },
        { 0x34c49476e131e0c0ULL, 0x723fd15da9a6d520ULL, },
        { 0xf8b9fc198693378eULL, 0xd8589336a7bd92acULL, },
        { 0x8328e62f75f51c48ULL, 0x5d5ec67813ba0208ULL, },
        { 0xf67c00c69a268e10ULL, 0x24ee76342a7ea4f8ULL, },
        { 0xa718ae0d06625288ULL, 0x39cf8119c06a7710ULL, },
        { 0x6b0d16b0abc4a956ULL, 0x9fe843f2be81349cULL, },
        { 0x34c49476e131e0c0ULL, 0x723fd15da9a6d520ULL, },    /*  72  */
        { 0xa718ae0d06625288ULL, 0x39cf8119c06a7710ULL, },
        { 0x58b45c54729e1600ULL, 0x4eb08cfe56564a28ULL, },
        { 0x1ca9c4f717006dceULL, 0xb4c94ed7546d07b4ULL, },
        { 0xf8b9fc198693378eULL, 0xd8589336a7bd92acULL, },
        { 0x6b0d16b0abc4a956ULL, 0x9fe843f2be81349cULL, },
        { 0x1ca9c4f717006dceULL, 0xb4c94ed7546d07b4ULL, },
        { 0xe09e2c9abc62c49cULL, 0x1ae210b05284c440ULL, },
};

    gettimeofday(&start, NULL);

    for (i = 0; i < PATTERN_INPUTS_SHORT_COUNT; i++) {
        for (j = 0; j < PATTERN_INPUTS_SHORT_COUNT; j++) {
            do_msa_ADDV_B(b128_pattern[i], b128_pattern[j],
                           b128_result[PATTERN_INPUTS_SHORT_COUNT * i + j]);
        }
    }

    for (i = 0; i < RANDOM_INPUTS_SHORT_COUNT; i++) {
        for (j = 0; j < RANDOM_INPUTS_SHORT_COUNT; j++) {
            do_msa_ADDV_B(b128_random[i], b128_random[j],
                           b128_result[((PATTERN_INPUTS_SHORT_COUNT) *
                                        (PATTERN_INPUTS_SHORT_COUNT)) +
                                       RANDOM_INPUTS_SHORT_COUNT * i + j]);
        }
    }

    gettimeofday(&end, NULL);

    elapsed_time = (end.tv_sec - start.tv_sec) * 1000.0;
    elapsed_time += (end.tv_usec - start.tv_usec) / 1000.0;

    ret = check_results(instruction_name, TEST_COUNT_TOTAL, elapsed_time,
                        &b128_result[0][0], &b128_expect[0][0]);

    return ret;
}
