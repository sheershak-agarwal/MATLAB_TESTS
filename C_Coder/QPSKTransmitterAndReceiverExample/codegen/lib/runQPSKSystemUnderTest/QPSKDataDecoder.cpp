//
// QPSKDataDecoder.cpp
//
// Code generation for function 'QPSKDataDecoder'
//

// Include files
#include "QPSKDataDecoder.h"
#include "Descrambler.h"
#include "ErrorRate.h"
#include "QPSKDemodulator.h"
#include "rt_nonfinite.h"
#include "runQPSKSystemUnderTest_data.h"
#include "runQPSKSystemUnderTest_rtwutil.h"
#include "coder_array.h"
#include <cmath>
#include <cstddef>
#include <cstring>
#include <stdio.h>
#include <string.h>

// Function Definitions
QPSKDataDecoder::QPSKDataDecoder()
{
  this->matlabCodegenIsDeleted = true;
}

QPSKDataDecoder::~QPSKDataDecoder()
{
  this->matlabCodegenDestructor();
}

void QPSKDataDecoder::matlabCodegenDestructor()
{
  if (!this->matlabCodegenIsDeleted) {
    this->matlabCodegenIsDeleted = true;
    if (this->isInitialized == 1) {
      this->isInitialized = 2;
      if (this->isSetupComplete) {
        if (this->pQPSKDemodulator.isInitialized == 1) {
          this->pQPSKDemodulator.isInitialized = 2;
        }
        if (this->pDescrambler.isInitialized == 1) {
          this->pDescrambler.isInitialized = 2;
        }
        if (this->pErrorRateCalc.isInitialized == 1) {
          this->pErrorRateCalc.isInitialized = 2;
        }
        this->pBER[0] = 0.0;
        this->pBER[1] = 0.0;
        this->pBER[2] = 0.0;
      }
    }
  }
}

void QPSKDataDecoder::step(const creal_T varargin_1[1133], boolean_T varargin_2,
                           double varargout_1[3])
{
  static const creal_T dcv[13]{{
                                   -0.70710678118654757, // re
                                   0.70710678118654757   // im
                               },
                               {
                                   -0.70710678118654757, // re
                                   0.70710678118654757   // im
                               },
                               {
                                   -0.70710678118654757, // re
                                   0.70710678118654757   // im
                               },
                               {
                                   -0.70710678118654757, // re
                                   0.70710678118654757   // im
                               },
                               {
                                   -0.70710678118654757, // re
                                   0.70710678118654757   // im
                               },
                               {
                                   0.70710678118654757, // re
                                   -0.70710678118654757 // im
                               },
                               {
                                   0.70710678118654757, // re
                                   -0.70710678118654757 // im
                               },
                               {
                                   -0.70710678118654757, // re
                                   0.70710678118654757   // im
                               },
                               {
                                   -0.70710678118654757, // re
                                   0.70710678118654757   // im
                               },
                               {
                                   0.70710678118654757, // re
                                   -0.70710678118654757 // im
                               },
                               {
                                   -0.70710678118654757, // re
                                   0.70710678118654757   // im
                               },
                               {
                                   0.70710678118654757, // re
                                   -0.70710678118654757 // im
                               },
                               {
                                   -0.70710678118654757, // re
                                   0.70710678118654757   // im
                               }};
  static const short iv1[1540]{
      1,    2,    3,    4,    5,    6,    7,    8,    9,    10,   11,   12,
      13,   14,   15,   16,   17,   18,   19,   20,   21,   22,   23,   24,
      25,   26,   27,   28,   29,   30,   31,   32,   33,   34,   35,   36,
      37,   38,   39,   40,   41,   42,   43,   44,   45,   46,   47,   48,
      49,   50,   51,   52,   53,   54,   55,   56,   57,   58,   59,   60,
      61,   62,   63,   64,   65,   66,   67,   68,   69,   70,   71,   72,
      73,   74,   75,   76,   77,   113,  114,  115,  116,  117,  118,  119,
      120,  121,  122,  123,  124,  125,  126,  127,  128,  129,  130,  131,
      132,  133,  134,  135,  136,  137,  138,  139,  140,  141,  142,  143,
      144,  145,  146,  147,  148,  149,  150,  151,  152,  153,  154,  155,
      156,  157,  158,  159,  160,  161,  162,  163,  164,  165,  166,  167,
      168,  169,  170,  171,  172,  173,  174,  175,  176,  177,  178,  179,
      180,  181,  182,  183,  184,  185,  186,  187,  188,  189,  225,  226,
      227,  228,  229,  230,  231,  232,  233,  234,  235,  236,  237,  238,
      239,  240,  241,  242,  243,  244,  245,  246,  247,  248,  249,  250,
      251,  252,  253,  254,  255,  256,  257,  258,  259,  260,  261,  262,
      263,  264,  265,  266,  267,  268,  269,  270,  271,  272,  273,  274,
      275,  276,  277,  278,  279,  280,  281,  282,  283,  284,  285,  286,
      287,  288,  289,  290,  291,  292,  293,  294,  295,  296,  297,  298,
      299,  300,  301,  337,  338,  339,  340,  341,  342,  343,  344,  345,
      346,  347,  348,  349,  350,  351,  352,  353,  354,  355,  356,  357,
      358,  359,  360,  361,  362,  363,  364,  365,  366,  367,  368,  369,
      370,  371,  372,  373,  374,  375,  376,  377,  378,  379,  380,  381,
      382,  383,  384,  385,  386,  387,  388,  389,  390,  391,  392,  393,
      394,  395,  396,  397,  398,  399,  400,  401,  402,  403,  404,  405,
      406,  407,  408,  409,  410,  411,  412,  413,  449,  450,  451,  452,
      453,  454,  455,  456,  457,  458,  459,  460,  461,  462,  463,  464,
      465,  466,  467,  468,  469,  470,  471,  472,  473,  474,  475,  476,
      477,  478,  479,  480,  481,  482,  483,  484,  485,  486,  487,  488,
      489,  490,  491,  492,  493,  494,  495,  496,  497,  498,  499,  500,
      501,  502,  503,  504,  505,  506,  507,  508,  509,  510,  511,  512,
      513,  514,  515,  516,  517,  518,  519,  520,  521,  522,  523,  524,
      525,  561,  562,  563,  564,  565,  566,  567,  568,  569,  570,  571,
      572,  573,  574,  575,  576,  577,  578,  579,  580,  581,  582,  583,
      584,  585,  586,  587,  588,  589,  590,  591,  592,  593,  594,  595,
      596,  597,  598,  599,  600,  601,  602,  603,  604,  605,  606,  607,
      608,  609,  610,  611,  612,  613,  614,  615,  616,  617,  618,  619,
      620,  621,  622,  623,  624,  625,  626,  627,  628,  629,  630,  631,
      632,  633,  634,  635,  636,  637,  673,  674,  675,  676,  677,  678,
      679,  680,  681,  682,  683,  684,  685,  686,  687,  688,  689,  690,
      691,  692,  693,  694,  695,  696,  697,  698,  699,  700,  701,  702,
      703,  704,  705,  706,  707,  708,  709,  710,  711,  712,  713,  714,
      715,  716,  717,  718,  719,  720,  721,  722,  723,  724,  725,  726,
      727,  728,  729,  730,  731,  732,  733,  734,  735,  736,  737,  738,
      739,  740,  741,  742,  743,  744,  745,  746,  747,  748,  749,  785,
      786,  787,  788,  789,  790,  791,  792,  793,  794,  795,  796,  797,
      798,  799,  800,  801,  802,  803,  804,  805,  806,  807,  808,  809,
      810,  811,  812,  813,  814,  815,  816,  817,  818,  819,  820,  821,
      822,  823,  824,  825,  826,  827,  828,  829,  830,  831,  832,  833,
      834,  835,  836,  837,  838,  839,  840,  841,  842,  843,  844,  845,
      846,  847,  848,  849,  850,  851,  852,  853,  854,  855,  856,  857,
      858,  859,  860,  861,  897,  898,  899,  900,  901,  902,  903,  904,
      905,  906,  907,  908,  909,  910,  911,  912,  913,  914,  915,  916,
      917,  918,  919,  920,  921,  922,  923,  924,  925,  926,  927,  928,
      929,  930,  931,  932,  933,  934,  935,  936,  937,  938,  939,  940,
      941,  942,  943,  944,  945,  946,  947,  948,  949,  950,  951,  952,
      953,  954,  955,  956,  957,  958,  959,  960,  961,  962,  963,  964,
      965,  966,  967,  968,  969,  970,  971,  972,  973,  1009, 1010, 1011,
      1012, 1013, 1014, 1015, 1016, 1017, 1018, 1019, 1020, 1021, 1022, 1023,
      1024, 1025, 1026, 1027, 1028, 1029, 1030, 1031, 1032, 1033, 1034, 1035,
      1036, 1037, 1038, 1039, 1040, 1041, 1042, 1043, 1044, 1045, 1046, 1047,
      1048, 1049, 1050, 1051, 1052, 1053, 1054, 1055, 1056, 1057, 1058, 1059,
      1060, 1061, 1062, 1063, 1064, 1065, 1066, 1067, 1068, 1069, 1070, 1071,
      1072, 1073, 1074, 1075, 1076, 1077, 1078, 1079, 1080, 1081, 1082, 1083,
      1084, 1085, 1121, 1122, 1123, 1124, 1125, 1126, 1127, 1128, 1129, 1130,
      1131, 1132, 1133, 1134, 1135, 1136, 1137, 1138, 1139, 1140, 1141, 1142,
      1143, 1144, 1145, 1146, 1147, 1148, 1149, 1150, 1151, 1152, 1153, 1154,
      1155, 1156, 1157, 1158, 1159, 1160, 1161, 1162, 1163, 1164, 1165, 1166,
      1167, 1168, 1169, 1170, 1171, 1172, 1173, 1174, 1175, 1176, 1177, 1178,
      1179, 1180, 1181, 1182, 1183, 1184, 1185, 1186, 1187, 1188, 1189, 1190,
      1191, 1192, 1193, 1194, 1195, 1196, 1197, 1233, 1234, 1235, 1236, 1237,
      1238, 1239, 1240, 1241, 1242, 1243, 1244, 1245, 1246, 1247, 1248, 1249,
      1250, 1251, 1252, 1253, 1254, 1255, 1256, 1257, 1258, 1259, 1260, 1261,
      1262, 1263, 1264, 1265, 1266, 1267, 1268, 1269, 1270, 1271, 1272, 1273,
      1274, 1275, 1276, 1277, 1278, 1279, 1280, 1281, 1282, 1283, 1284, 1285,
      1286, 1287, 1288, 1289, 1290, 1291, 1292, 1293, 1294, 1295, 1296, 1297,
      1298, 1299, 1300, 1301, 1302, 1303, 1304, 1305, 1306, 1307, 1308, 1309,
      1345, 1346, 1347, 1348, 1349, 1350, 1351, 1352, 1353, 1354, 1355, 1356,
      1357, 1358, 1359, 1360, 1361, 1362, 1363, 1364, 1365, 1366, 1367, 1368,
      1369, 1370, 1371, 1372, 1373, 1374, 1375, 1376, 1377, 1378, 1379, 1380,
      1381, 1382, 1383, 1384, 1385, 1386, 1387, 1388, 1389, 1390, 1391, 1392,
      1393, 1394, 1395, 1396, 1397, 1398, 1399, 1400, 1401, 1402, 1403, 1404,
      1405, 1406, 1407, 1408, 1409, 1410, 1411, 1412, 1413, 1414, 1415, 1416,
      1417, 1418, 1419, 1420, 1421, 1457, 1458, 1459, 1460, 1461, 1462, 1463,
      1464, 1465, 1466, 1467, 1468, 1469, 1470, 1471, 1472, 1473, 1474, 1475,
      1476, 1477, 1478, 1479, 1480, 1481, 1482, 1483, 1484, 1485, 1486, 1487,
      1488, 1489, 1490, 1491, 1492, 1493, 1494, 1495, 1496, 1497, 1498, 1499,
      1500, 1501, 1502, 1503, 1504, 1505, 1506, 1507, 1508, 1509, 1510, 1511,
      1512, 1513, 1514, 1515, 1516, 1517, 1518, 1519, 1520, 1521, 1522, 1523,
      1524, 1525, 1526, 1527, 1528, 1529, 1530, 1531, 1532, 1533, 1569, 1570,
      1571, 1572, 1573, 1574, 1575, 1576, 1577, 1578, 1579, 1580, 1581, 1582,
      1583, 1584, 1585, 1586, 1587, 1588, 1589, 1590, 1591, 1592, 1593, 1594,
      1595, 1596, 1597, 1598, 1599, 1600, 1601, 1602, 1603, 1604, 1605, 1606,
      1607, 1608, 1609, 1610, 1611, 1612, 1613, 1614, 1615, 1616, 1617, 1618,
      1619, 1620, 1621, 1622, 1623, 1624, 1625, 1626, 1627, 1628, 1629, 1630,
      1631, 1632, 1633, 1634, 1635, 1636, 1637, 1638, 1639, 1640, 1641, 1642,
      1643, 1644, 1645, 1681, 1682, 1683, 1684, 1685, 1686, 1687, 1688, 1689,
      1690, 1691, 1692, 1693, 1694, 1695, 1696, 1697, 1698, 1699, 1700, 1701,
      1702, 1703, 1704, 1705, 1706, 1707, 1708, 1709, 1710, 1711, 1712, 1713,
      1714, 1715, 1716, 1717, 1718, 1719, 1720, 1721, 1722, 1723, 1724, 1725,
      1726, 1727, 1728, 1729, 1730, 1731, 1732, 1733, 1734, 1735, 1736, 1737,
      1738, 1739, 1740, 1741, 1742, 1743, 1744, 1745, 1746, 1747, 1748, 1749,
      1750, 1751, 1752, 1753, 1754, 1755, 1756, 1757, 1793, 1794, 1795, 1796,
      1797, 1798, 1799, 1800, 1801, 1802, 1803, 1804, 1805, 1806, 1807, 1808,
      1809, 1810, 1811, 1812, 1813, 1814, 1815, 1816, 1817, 1818, 1819, 1820,
      1821, 1822, 1823, 1824, 1825, 1826, 1827, 1828, 1829, 1830, 1831, 1832,
      1833, 1834, 1835, 1836, 1837, 1838, 1839, 1840, 1841, 1842, 1843, 1844,
      1845, 1846, 1847, 1848, 1849, 1850, 1851, 1852, 1853, 1854, 1855, 1856,
      1857, 1858, 1859, 1860, 1861, 1862, 1863, 1864, 1865, 1866, 1867, 1868,
      1869, 1905, 1906, 1907, 1908, 1909, 1910, 1911, 1912, 1913, 1914, 1915,
      1916, 1917, 1918, 1919, 1920, 1921, 1922, 1923, 1924, 1925, 1926, 1927,
      1928, 1929, 1930, 1931, 1932, 1933, 1934, 1935, 1936, 1937, 1938, 1939,
      1940, 1941, 1942, 1943, 1944, 1945, 1946, 1947, 1948, 1949, 1950, 1951,
      1952, 1953, 1954, 1955, 1956, 1957, 1958, 1959, 1960, 1961, 1962, 1963,
      1964, 1965, 1966, 1967, 1968, 1969, 1970, 1971, 1972, 1973, 1974, 1975,
      1976, 1977, 1978, 1979, 1980, 1981, 2017, 2018, 2019, 2020, 2021, 2022,
      2023, 2024, 2025, 2026, 2027, 2028, 2029, 2030, 2031, 2032, 2033, 2034,
      2035, 2036, 2037, 2038, 2039, 2040, 2041, 2042, 2043, 2044, 2045, 2046,
      2047, 2048, 2049, 2050, 2051, 2052, 2053, 2054, 2055, 2056, 2057, 2058,
      2059, 2060, 2061, 2062, 2063, 2064, 2065, 2066, 2067, 2068, 2069, 2070,
      2071, 2072, 2073, 2074, 2075, 2076, 2077, 2078, 2079, 2080, 2081, 2082,
      2083, 2084, 2085, 2086, 2087, 2088, 2089, 2090, 2091, 2092, 2093, 2129,
      2130, 2131, 2132, 2133, 2134, 2135, 2136, 2137, 2138, 2139, 2140, 2141,
      2142, 2143, 2144, 2145, 2146, 2147, 2148, 2149, 2150, 2151, 2152, 2153,
      2154, 2155, 2156, 2157, 2158, 2159, 2160, 2161, 2162, 2163, 2164, 2165,
      2166, 2167, 2168, 2169, 2170, 2171, 2172, 2173, 2174, 2175, 2176, 2177,
      2178, 2179, 2180, 2181, 2182, 2183, 2184, 2185, 2186, 2187, 2188, 2189,
      2190, 2191, 2192, 2193, 2194, 2195, 2196, 2197, 2198, 2199, 2200, 2201,
      2202, 2203, 2204, 2205};
  static const signed char iv[5]{1, 1, 1, 0, 1};
  coder::commcodegen::Descrambler *obj;
  coder::commcodegen::ErrorRate *obj_tmp;
  coder::array<char, 2U> charStr;
  comm_Descrambler_6 *b_obj;
  comm_ErrorRate_7 *c_obj;
  creal_T phShiftedData[1133];
  creal_T x[13];
  double b[2240];
  double msgSet[320];
  double tmp;
  int i;
  int j;
  int nbytes;
  signed char demodOut[2266];
  signed char deScrData[2240];
  char b_varargin_1[321];
  if (this->isInitialized != 1) {
    this->isSetupComplete = false;
    this->isInitialized = 1;
    this->pQPSKDemodulator.isInitialized = 0;
    // System object Constructor function: comm.QPSKDemodulator
    this->pQPSKDemodulator.matlabCodegenIsDeleted = false;
    obj = &this->pDescrambler;
    this->pDescrambler.isInitialized = 0;
    // System object Constructor function: comm.Descrambler
    for (i = 0; i < 5; i++) {
      obj->cSFunObject.P0_Polynomial[i] = static_cast<unsigned char>(iv[i]);
    }
    obj->cSFunObject.P1_IniState[0] = 0;
    obj->cSFunObject.P1_IniState[1] = 0;
    obj->cSFunObject.P1_IniState[2] = 0;
    obj->cSFunObject.P1_IniState[3] = 0;
    this->pDescrambler.matlabCodegenIsDeleted = false;
    //  For BER calculation masks
    obj_tmp = &this->pErrorRateCalc;
    this->pErrorRateCalc.isInitialized = 0;
    // System object Constructor function: comm.ErrorRate
    for (i = 0; i < 1540; i++) {
      obj_tmp->cSFunObject.P0_Subframe[i] = iv1[i];
    }
    this->pErrorRateCalc.matlabCodegenIsDeleted = false;
    //  Since we only calculate BER on message part, 000s are not
    //  necessary here, they are just place-holder.
    for (i = 0; i < 20; i++) {
      nbytes = snprintf(nullptr, 0, "%s %03lld\n", "Hello world",
                        static_cast<long long>(i));
      charStr.set_size(1, nbytes + 1);
      snprintf(&charStr[0], (size_t)(nbytes + 1), "%s %03lld\n", "Hello world",
               static_cast<long long>(i));
      if (1 > nbytes) {
        nbytes = 0;
      }
      charStr.set_size(charStr.size(0), nbytes);
      nbytes = i << 4;
      for (j = 0; j < 16; j++) {
        msgSet[j + nbytes] = static_cast<unsigned char>(charStr[j]);
      }
    }
    std::memset(&b[0], 0, 2240U * sizeof(double));
    for (i = 0; i < 320; i++) {
      j = 1;
      tmp = msgSet[i];
      while ((j <= 7) && (tmp > 0.0)) {
        b[i + 320 * (j - 1)] = rt_remd_snf(tmp, 2.0);
        tmp /= 2.0;
        tmp = std::floor(tmp);
        j++;
      }
    }
    for (j = 0; j < 7; j++) {
      for (i = 0; i < 320; i++) {
        deScrData[i + 320 * j] = static_cast<signed char>(b[i + 320 * (6 - j)]);
      }
    }
    for (j = 0; j < 7; j++) {
      for (i = 0; i < 320; i++) {
        nbytes = i + 320 * j;
        b[nbytes] = deScrData[nbytes];
      }
    }
    for (j = 0; j < 320; j++) {
      for (i = 0; i < 7; i++) {
        deScrData[i + 7 * j] = static_cast<signed char>(b[j + 320 * i]);
      }
    }
    for (j = 0; j < 2240; j++) {
      this->pTargetBits[j] = deScrData[j];
    }
    this->isSetupComplete = true;
    if (this->pDescrambler.isInitialized == 1) {
      // System object Initialization function: comm.Descrambler
      this->pDescrambler.cSFunObject.W0_shiftReg[0] =
          this->pDescrambler.cSFunObject.P1_IniState[0];
      this->pDescrambler.cSFunObject.W0_shiftReg[1] =
          this->pDescrambler.cSFunObject.P1_IniState[1];
      this->pDescrambler.cSFunObject.W0_shiftReg[2] =
          this->pDescrambler.cSFunObject.P1_IniState[2];
      this->pDescrambler.cSFunObject.W0_shiftReg[3] =
          this->pDescrambler.cSFunObject.P1_IniState[3];
    }
    if (this->pErrorRateCalc.isInitialized == 1) {
      c_obj = &this->pErrorRateCalc.cSFunObject;
      // System object Initialization function: comm.ErrorRate
      this->pErrorRateCalc.cSFunObject.W0_errors = 0.0;
      this->pErrorRateCalc.cSFunObject.W1_symbols = 0.0;
      this->pErrorRateCalc.cSFunObject.W2_STDelay = 0;
      this->pErrorRateCalc.cSFunObject.W4_curTx = 0;
      for (i = 0; i < 2240; i++) {
        c_obj->W5_useFrame[i] = false;
      }
      for (i = 0; i < 1540; i++) {
        nbytes = static_cast<int>(std::floor(c_obj->P0_Subframe[i]));
        if (nbytes > 0) {
          c_obj->W5_useFrame[nbytes - 1] = true;
        }
      }
    }
    this->pBER[0] = 0.0;
    this->pBER[1] = 0.0;
    this->pBER[2] = 0.0;
  }
  if (varargin_2) {
    double d;
    double d1;
    double r;
    double x_re;
    //  Phase ambiguity estimation
    for (i = 0; i < 13; i++) {
      d = dcv[i].re;
      d1 = dcv[i].im;
      tmp = varargin_1[i].re;
      r = varargin_1[i].im;
      x[i].re = d * tmp - d1 * r;
      x[i].im = d * r + d1 * tmp;
    }
    x_re = x[0].re;
    tmp = x[0].im;
    for (nbytes = 0; nbytes < 12; nbytes++) {
      x_re += x[nbytes + 1].re;
      tmp += x[nbytes + 1].im;
    }
    if (tmp == 0.0) {
      r = x_re / 13.0;
      tmp = 0.0;
    } else if (x_re == 0.0) {
      r = 0.0;
      tmp /= 13.0;
    } else {
      r = x_re / 13.0;
      tmp /= 13.0;
    }
    //  Compensating for the phase ambiguity
    tmp = std::round(rt_atan2d_snf(tmp, r) * 2.0 / 3.1415926535897931) / 2.0 *
          3.1415926535897931;
    x_re = tmp * 0.0;
    if (-tmp == 0.0) {
      x_re = std::exp(x_re);
      tmp = 0.0;
    } else {
      r = std::exp(x_re / 2.0);
      x_re = r * (r * std::cos(-tmp));
      tmp = r * (r * std::sin(-tmp));
    }
    for (i = 0; i < 1133; i++) {
      d = varargin_1[i].re;
      d1 = varargin_1[i].im;
      phShiftedData[i].re = d * x_re - d1 * tmp;
      phShiftedData[i].im = d * tmp + d1 * x_re;
    }
    //  Demodulating the phase recovered data
    if (this->pQPSKDemodulator.isInitialized != 1) {
      this->pQPSKDemodulator.isSetupComplete = false;
      this->pQPSKDemodulator.isInitialized = 1;
      this->pQPSKDemodulator.isSetupComplete = true;
    }
    // System object Outputs function: comm.QPSKDemodulator
    for (j = 0; j < 1133; j++) {
      d = phShiftedData[j].re;
      if (d > 0.0) {
        if (phShiftedData[j].im >= 0.0) {
          nbytes = 0;
        } else {
          nbytes = 3;
        }
      } else if (d < 0.0) {
        if (phShiftedData[j].im <= 0.0) {
          nbytes = 2;
        } else {
          nbytes = 1;
        }
      } else {
        d = phShiftedData[j].im;
        if (d < 0.0) {
          nbytes = 3;
        } else {
          nbytes = (d > 0.0);
        }
      }
      nbytes ^= nbytes >> 1;
      i = j << 1;
      demodOut[i + 1] = static_cast<signed char>(nbytes % 2);
      nbytes >>= 1;
      demodOut[i] = static_cast<signed char>(nbytes % 2);
    }
    //  Performs descrambling on only payload part
    if (this->pDescrambler.isInitialized != 1) {
      this->pDescrambler.isSetupComplete = false;
      this->pDescrambler.isInitialized = 1;
      this->pDescrambler.isSetupComplete = true;
      // System object Initialization function: comm.Descrambler
      this->pDescrambler.cSFunObject.W0_shiftReg[0] =
          this->pDescrambler.cSFunObject.P1_IniState[0];
      this->pDescrambler.cSFunObject.W0_shiftReg[1] =
          this->pDescrambler.cSFunObject.P1_IniState[1];
      this->pDescrambler.cSFunObject.W0_shiftReg[2] =
          this->pDescrambler.cSFunObject.P1_IniState[2];
      this->pDescrambler.cSFunObject.W0_shiftReg[3] =
          this->pDescrambler.cSFunObject.P1_IniState[3];
    }
    b_obj = &this->pDescrambler.cSFunObject;
    // System object Outputs function: comm.Descrambler
    for (j = 0; j < 2240; j++) {
      nbytes = demodOut[j + 26];
      i = nbytes - static_cast<unsigned char>(b_obj->W0_shiftReg[0] *
                                              b_obj->P0_Polynomial[1]);
      i -= static_cast<unsigned char>(b_obj->W0_shiftReg[1] *
                                      b_obj->P0_Polynomial[2]);
      i -= static_cast<unsigned char>(b_obj->W0_shiftReg[2] *
                                      b_obj->P0_Polynomial[3]);
      for (i -= static_cast<unsigned char>(b_obj->W0_shiftReg[3] *
                                           b_obj->P0_Polynomial[4]);
           i < 0; i += 2) {
      }
      i %= 2;
      deScrData[j] = static_cast<signed char>(i);
      b_obj->W0_shiftReg[3] = b_obj->W0_shiftReg[2];
      b_obj->W0_shiftReg[2] = b_obj->W0_shiftReg[1];
      b_obj->W0_shiftReg[1] = b_obj->W0_shiftReg[0];
      b_obj->W0_shiftReg[0U] = nbytes;
    }
    //  Recovering the message from the data
    for (j = 0; j < 7; j++) {
      for (i = 0; i < 320; i++) {
        b[i + 320 * j] = deScrData[j + 7 * i];
      }
    }
    tmp = 1.0;
    std::memset(&msgSet[0], 0, 320U * sizeof(double));
    for (j = 0; j < 7; j++) {
      for (i = 0; i < 320; i++) {
        r = msgSet[i];
        if (b[i + 320 * (6 - j)] != 0.0) {
          r += tmp;
        }
        msgSet[i] = r;
      }
      tmp *= 2.0;
    }
    for (j = 0; j < 320; j++) {
      signed char b_i;
      d = msgSet[j];
      if (d < 128.0) {
        b_i = static_cast<signed char>(d);
      } else {
        b_i = MAX_int8_T;
      }
      b_varargin_1[j] = b_i;
    }
    b_varargin_1[320] = '\x00';
    printf("%s", &b_varargin_1[0]);
    fflush(stdout);
    //  Perform BER calculation only on message part
    obj_tmp = &this->pErrorRateCalc;
    for (j = 0; j < 2240; j++) {
      b[j] = this->pTargetBits[j];
    }
    if (this->pErrorRateCalc.isInitialized != 1) {
      this->pErrorRateCalc.isSetupComplete = false;
      this->pErrorRateCalc.isInitialized = 1;
      this->pErrorRateCalc.isSetupComplete = true;
      c_obj = &this->pErrorRateCalc.cSFunObject;
      // System object Initialization function: comm.ErrorRate
      this->pErrorRateCalc.cSFunObject.W0_errors = 0.0;
      this->pErrorRateCalc.cSFunObject.W1_symbols = 0.0;
      this->pErrorRateCalc.cSFunObject.W2_STDelay = 0;
      this->pErrorRateCalc.cSFunObject.W4_curTx = 0;
      for (i = 0; i < 2240; i++) {
        c_obj->W5_useFrame[i] = false;
      }
      for (i = 0; i < 1540; i++) {
        nbytes = static_cast<int>(std::floor(c_obj->P0_Subframe[i]));
        if (nbytes > 0) {
          c_obj->W5_useFrame[nbytes - 1] = true;
        }
      }
    }
    c_obj = &this->pErrorRateCalc.cSFunObject;
    // System object Outputs function: comm.ErrorRate
    tmp = 0.0;
    r = 0.0;
    varargout_1[0U] = 0.0;
    for (nbytes = 0; nbytes < 2240; nbytes++) {
      boolean_T cur_fr;
      c_obj->W3_txBuff = b[nbytes];
      cur_fr = c_obj->W5_useFrame[nbytes];
      if (c_obj->W4_curTx == 0) {
        c_obj->W4_curTx = 0;
      } else {
        c_obj->W4_curTx++;
      }
      if (c_obj->W2_STDelay < 0) {
        c_obj->W2_STDelay++;
      } else if (cur_fr) {
        r++;
        if (c_obj->W3_txBuff != deScrData[nbytes]) {
          tmp++;
        }
      }
    }
    obj_tmp->cSFunObject.W1_symbols += r;
    obj_tmp->cSFunObject.W0_errors += tmp;
    if (obj_tmp->cSFunObject.W1_symbols > 0.0) {
      varargout_1[0U] =
          obj_tmp->cSFunObject.W0_errors / obj_tmp->cSFunObject.W1_symbols;
    }
    varargout_1[1U] = obj_tmp->cSFunObject.W0_errors;
    varargout_1[2U] = obj_tmp->cSFunObject.W1_symbols;
    this->pBER[0] = varargout_1[0];
    this->pBER[1] = varargout_1[1];
    this->pBER[2] = varargout_1[2];
  }
  varargout_1[0] = this->pBER[0];
  varargout_1[1] = this->pBER[1];
  varargout_1[2] = this->pBER[2];
}

// End of code generation (QPSKDataDecoder.cpp)
