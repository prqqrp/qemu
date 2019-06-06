/*
 *  Test program for MSA instruction AVE_U.H
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
    char *instruction_name = "AVE_U.H";
    int32_t ret;
    uint32_t i, j;
    struct timeval start, end;
    double elapsed_time;

    uint64_t b128_result[TEST_COUNT_TOTAL][2];
    uint64_t b128_expect[TEST_COUNT_TOTAL][2] = {
        { 0xffffffffffffffffULL, 0xffffffffffffffffULL, },    /*   0  */
        { 0x7fff7fff7fff7fffULL, 0x7fff7fff7fff7fffULL, },
        { 0xd554d554d554d554ULL, 0xd554d554d554d554ULL, },
        { 0xaaaaaaaaaaaaaaaaULL, 0xaaaaaaaaaaaaaaaaULL, },
        { 0xe665e665e665e665ULL, 0xe665e665e665e665ULL, },
        { 0x9999999999999999ULL, 0x9999999999999999ULL, },
        { 0xf1c69c71c71bf1c6ULL, 0x9c71c71bf1c69c71ULL, },
        { 0x8e38e38db8e38e38ULL, 0xe38db8e38e38e38dULL, },
        { 0x7fff7fff7fff7fffULL, 0x7fff7fff7fff7fffULL, },    /*   8  */
        { 0x0000000000000000ULL, 0x0000000000000000ULL, },
        { 0x5555555555555555ULL, 0x5555555555555555ULL, },
        { 0x2aaa2aaa2aaa2aaaULL, 0x2aaa2aaa2aaa2aaaULL, },
        { 0x6666666666666666ULL, 0x6666666666666666ULL, },
        { 0x1999199919991999ULL, 0x1999199919991999ULL, },
        { 0x71c71c71471c71c7ULL, 0x1c71471c71c71c71ULL, },
        { 0x0e38638e38e30e38ULL, 0x638e38e30e38638eULL, },
        { 0xd554d554d554d554ULL, 0xd554d554d554d554ULL, },    /*  16  */
        { 0x5555555555555555ULL, 0x5555555555555555ULL, },
        { 0xaaaaaaaaaaaaaaaaULL, 0xaaaaaaaaaaaaaaaaULL, },
        { 0x7fff7fff7fff7fffULL, 0x7fff7fff7fff7fffULL, },
        { 0xbbbbbbbbbbbbbbbbULL, 0xbbbbbbbbbbbbbbbbULL, },
        { 0x6eee6eee6eee6eeeULL, 0x6eee6eee6eee6eeeULL, },
        { 0xc71c71c69c71c71cULL, 0x71c69c71c71c71c6ULL, },
        { 0x638db8e38e38638dULL, 0xb8e38e38638db8e3ULL, },
        { 0xaaaaaaaaaaaaaaaaULL, 0xaaaaaaaaaaaaaaaaULL, },    /*  24  */
        { 0x2aaa2aaa2aaa2aaaULL, 0x2aaa2aaa2aaa2aaaULL, },
        { 0x7fff7fff7fff7fffULL, 0x7fff7fff7fff7fffULL, },
        { 0x5555555555555555ULL, 0x5555555555555555ULL, },
        { 0x9110911091109110ULL, 0x9110911091109110ULL, },
        { 0x4444444444444444ULL, 0x4444444444444444ULL, },
        { 0x9c71471c71c69c71ULL, 0x471c71c69c71471cULL, },
        { 0x38e38e38638e38e3ULL, 0x8e38638e38e38e38ULL, },
        { 0xe665e665e665e665ULL, 0xe665e665e665e665ULL, },    /*  32  */
        { 0x6666666666666666ULL, 0x6666666666666666ULL, },
        { 0xbbbbbbbbbbbbbbbbULL, 0xbbbbbbbbbbbbbbbbULL, },
        { 0x9110911091109110ULL, 0x9110911091109110ULL, },
        { 0xccccccccccccccccULL, 0xccccccccccccccccULL, },
        { 0x7fff7fff7fff7fffULL, 0x7fff7fff7fff7fffULL, },
        { 0xd82d82d7ad82d82dULL, 0x82d7ad82d82d82d7ULL, },
        { 0x749ec9f49f49749eULL, 0xc9f49f49749ec9f4ULL, },
        { 0x9999999999999999ULL, 0x9999999999999999ULL, },    /*  40  */
        { 0x1999199919991999ULL, 0x1999199919991999ULL, },
        { 0x6eee6eee6eee6eeeULL, 0x6eee6eee6eee6eeeULL, },
        { 0x4444444444444444ULL, 0x4444444444444444ULL, },
        { 0x7fff7fff7fff7fffULL, 0x7fff7fff7fff7fffULL, },
        { 0x3333333333333333ULL, 0x3333333333333333ULL, },
        { 0x8b60360b60b58b60ULL, 0x360b60b58b60360bULL, },
        { 0x27d27d27527d27d2ULL, 0x7d27527d27d27d27ULL, },
        { 0xf1c69c71c71bf1c6ULL, 0x9c71c71bf1c69c71ULL, },    /*  48  */
        { 0x71c71c71471c71c7ULL, 0x1c71471c71c71c71ULL, },
        { 0xc71c71c69c71c71cULL, 0x71c69c71c71c71c6ULL, },
        { 0x9c71471c71c69c71ULL, 0x471c71c69c71471cULL, },
        { 0xd82d82d7ad82d82dULL, 0x82d7ad82d82d82d7ULL, },
        { 0x8b60360b60b58b60ULL, 0x360b60b58b60360bULL, },
        { 0xe38e38e38e38e38eULL, 0x38e38e38e38e38e3ULL, },
        { 0x7fff7fff7fff7fffULL, 0x7fff7fff7fff7fffULL, },
        { 0x8e38e38db8e38e38ULL, 0xe38db8e38e38e38dULL, },    /*  56  */
        { 0x0e38638e38e30e38ULL, 0x638e38e30e38638eULL, },
        { 0x638db8e38e38638dULL, 0xb8e38e38638db8e3ULL, },
        { 0x38e38e38638e38e3ULL, 0x8e38638e38e38e38ULL, },
        { 0x749ec9f49f49749eULL, 0xc9f49f49749ec9f4ULL, },
        { 0x27d27d27527d27d2ULL, 0x7d27527d27d27d27ULL, },
        { 0x7fff7fff7fff7fffULL, 0x7fff7fff7fff7fffULL, },
        { 0x1c71c71c71c71c71ULL, 0xc71c71c71c71c71cULL, },
        { 0x886ae6cc28625540ULL, 0x4b670b5efe7bb00cULL, },    /*  64  */
        { 0xc21473973afa8e24ULL, 0x2f2f633c89dd8184ULL, },
        { 0x9a62cabb71187060ULL, 0x399f692ed4d36a90ULL, },
        { 0x7c5c7e8c43499bc7ULL, 0x6cac4a1bd3dec956ULL, },
        { 0xc21473973afa8e24ULL, 0x2f2f633c89dd8184ULL, },
        { 0xfbbe00634d93c708ULL, 0x12f7bb1a153f52fcULL, },
        { 0xd40c578683b1a944ULL, 0x1d67c10c60353c08ULL, },
        { 0xb6060b5855e2d4abULL, 0x5074a1f95f409aceULL, },
        { 0x9a62cabb71187060ULL, 0x399f692ed4d36a90ULL, },    /*  72  */
        { 0xd40c578683b1a944ULL, 0x1d67c10c60353c08ULL, },
        { 0xac5aaeaab9cf8b80ULL, 0x27d8c6ffab2b2514ULL, },
        { 0x8e54627b8c00b6e7ULL, 0x5ae4a7ebaa3683daULL, },
        { 0x7c5c7e8c43499bc7ULL, 0x6cac4a1bd3dec956ULL, },
        { 0xb6060b5855e2d4abULL, 0x5074a1f95f409aceULL, },
        { 0x8e54627b8c00b6e7ULL, 0x5ae4a7ebaa3683daULL, },
        { 0x704f164d5e31e24eULL, 0x8df188d8a942e2a0ULL, },
};

    gettimeofday(&start, NULL);

    for (i = 0; i < PATTERN_INPUTS_SHORT_COUNT; i++) {
        for (j = 0; j < PATTERN_INPUTS_SHORT_COUNT; j++) {
            do_msa_AVE_U_H(b128_pattern[i], b128_pattern[j],
                           b128_result[PATTERN_INPUTS_SHORT_COUNT * i + j]);
        }
    }

    for (i = 0; i < RANDOM_INPUTS_SHORT_COUNT; i++) {
        for (j = 0; j < RANDOM_INPUTS_SHORT_COUNT; j++) {
            do_msa_AVE_U_H(b128_random[i], b128_random[j],
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
