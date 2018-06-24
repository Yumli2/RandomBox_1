/*
 * Copyright 2010-2015 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Additions Copyright 2016 Espressif Systems (Shanghai) PTE LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

/**
 * @file aws_iot_certifcates.c
 * @brief File to store the AWS certificates in the form of arrays
 */

#ifdef __cplusplus
extern "C" {
#endif

const char aws_root_ca_pem[] = {"-----BEGIN CERTIFICATE-----\n\
MIIE0zCCA7ugAwIBAgIQGNrRniZ96LtKIVjNzGs7SjANBgkqhkiG9w0BAQUFADCB\n\
yjELMAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMR8wHQYDVQQL\n\
ExZWZXJpU2lnbiBUcnVzdCBOZXR3b3JrMTowOAYDVQQLEzEoYykgMjAwNiBWZXJp\n\
U2lnbiwgSW5jLiAtIEZvciBhdXRob3JpemVkIHVzZSBvbmx5MUUwQwYDVQQDEzxW\n\
ZXJpU2lnbiBDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0\n\
aG9yaXR5IC0gRzUwHhcNMDYxMTA4MDAwMDAwWhcNMzYwNzE2MjM1OTU5WjCByjEL\n\
MAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMR8wHQYDVQQLExZW\n\
ZXJpU2lnbiBUcnVzdCBOZXR3b3JrMTowOAYDVQQLEzEoYykgMjAwNiBWZXJpU2ln\n\
biwgSW5jLiAtIEZvciBhdXRob3JpemVkIHVzZSBvbmx5MUUwQwYDVQQDEzxWZXJp\n\
U2lnbiBDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0aG9y\n\
aXR5IC0gRzUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCvJAgIKXo1\n\
nmAMqudLO07cfLw8RRy7K+D+KQL5VwijZIUVJ/XxrcgxiV0i6CqqpkKzj/i5Vbex\n\
t0uz/o9+B1fs70PbZmIVYc9gDaTY3vjgw2IIPVQT60nKWVSFJuUrjxuf6/WhkcIz\n\
SdhDY2pSS9KP6HBRTdGJaXvHcPaz3BJ023tdS1bTlr8Vd6Gw9KIl8q8ckmcY5fQG\n\
BO+QueQA5N06tRn/Arr0PO7gi+s3i+z016zy9vA9r911kTMZHRxAy3QkGSGT2RT+\n\
rCpSx4/VBEnkjWNHiDxpg8v+R70rfk/Fla4OndTRQ8Bnc+MUCH7lP59zuDMKz10/\n\
NIeWiu5T6CUVAgMBAAGjgbIwga8wDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8E\n\
BAMCAQYwbQYIKwYBBQUHAQwEYTBfoV2gWzBZMFcwVRYJaW1hZ2UvZ2lmMCEwHzAH\n\
BgUrDgMCGgQUj+XTGoasjY5rw8+AatRIGCx7GS4wJRYjaHR0cDovL2xvZ28udmVy\n\
aXNpZ24uY29tL3ZzbG9nby5naWYwHQYDVR0OBBYEFH/TZafC3ey78DAJ80M5+gKv\n\
MzEzMA0GCSqGSIb3DQEBBQUAA4IBAQCTJEowX2LP2BqYLz3q3JktvXf2pXkiOOzE\n\
p6B4Eq1iDkVwZMXnl2YtmAl+X6/WzChl8gGqCBpH3vn5fJJaCGkgDdk+bW48DW7Y\n\
5gaRQBi5+MHt39tBquCWIMnNZBU4gcmU7qKEKQsTb47bDN0lAtukixlE0kF6BWlK\n\
WE9gyn6CagsCqiUXObXbf+eEZSqVir2G3l6BFoMtEMze/aiCKm0oHw0LxOXnGiYZ\n\
4fQRbxC1lfznQgUy286dUV4otp6F01vvpX1FQHKOtw5rDgb7MzVIcbidJ4vEZV8N\n\
hnacRHr2lVz2XTIIM6RUthg/aFzyQkqFOFSDX9HoLPKsEdao7WNq\n\
-----END CERTIFICATE-----\n"};

const char certificate_pem_crt[] = {"-----BEGIN CERTIFICATE-----\n\
MIIDWTCCAkGgAwIBAgIUWDW4qyby6GFSC9CET+wveQ0bxgswDQYJKoZIhvcNAQEL\n\
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n\
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTE4MDUyMjAyNTAz\n\
MFoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\n\
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAK61/T9JngPrf0hjJHb5\n\
RGxwTqTW6ylKOK594/k4pnGDBIqP8o6zsqEo4fAN30KH7jr3ToYohWUj79ALT2uQ\n\
cESK/yZBYW/zbO3Adv6/7biMH2I+aKbiWeIDJ36IPoSJeQbfrVKXxmFpz08/Ocbr\n\
8QNjO8pt56eRqI8I8gNzCsUZrFOvfGzfgbzSsGMeSsjeBaXjf3ICiwz/S1ICK3TD\n\
ghXiWiA9HJ67+mCo1DgbFxIL/z3J8hCHc6OR8RaxUWMJ//5zr26lD0ynzCITi1eD\n\
3lopqMO4QHYG+rFRJ8rN8lSD9MIbFI6ZbN5BTT93R66/NboLmC8l1PB5/wcxtPr9\n\
nmMCAwEAAaNgMF4wHwYDVR0jBBgwFoAU5NRoFzqjyOoaKE8VZneA42/pcw8wHQYD\n\
VR0OBBYEFIj4X2PiYcpLkAYeZZGeNb++z1dtMAwGA1UdEwEB/wQCMAAwDgYDVR0P\n\
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQA4R2E0+RgjK5MOI96jkrizxzNP\n\
7k8/R8lViN0vAoB61o6WJKSWsiCUzSvNSBqsSsLrcWKpKHwGGUKp/8Hq0uSIINW1\n\
qnp8SSV1SidkujNdF/occ2Aal4JRCp5k/L3dQ2/SFYWd7Ygp1qB5YbNnsH5LckMh\n\
PI2/PYXfOMGDugpYmGWTrWfnsHNEW2HZyPn6x/ka9yJVzOYkImF/C6ESsZ71yri4\n\
Ur0PUo8/ardBMQpkO8nHtvFmivoeoicTXQ9IRAVe4ND+IQwuieD0+gBN1MxQyA6p\n\
Au7man2IQud8ZMkLVGYNdDg3nj1IT6l/QzDmDhbXvpdUjATbbD5WtjHCgWO0\n\
-----END CERTIFICATE-----\n"};

const char private_pem_key[] = {"-----BEGIN RSA PRIVATE KEY-----\n\
MIIEowIBAAKCAQEArrX9P0meA+t/SGMkdvlEbHBOpNbrKUo4rn3j+TimcYMEio/y\n\
jrOyoSjh8A3fQofuOvdOhiiFZSPv0AtPa5BwRIr/JkFhb/Ns7cB2/r/tuIwfYj5o\n\
puJZ4gMnfog+hIl5Bt+tUpfGYWnPTz85xuvxA2M7ym3np5GojwjyA3MKxRmsU698\n\
bN+BvNKwYx5KyN4FpeN/cgKLDP9LUgIrdMOCFeJaID0cnrv6YKjUOBsXEgv/Pcny\n\
EIdzo5HxFrFRYwn//nOvbqUPTKfMIhOLV4PeWimow7hAdgb6sVEnys3yVIP0whsU\n\
jpls3kFNP3dHrr81uguYLyXU8Hn/BzG0+v2eYwIDAQABAoIBACrRk5W1NzMCvplB\n\
Iyi9gtWI2N1xhwUBmc66L+texPxA/hXvnaT3yanR2T36SGOH6Q0um2IqADd/jUDR\n\
5M8aAUnrPwljMLw9Ts8eQovBAkQeo3pyjTeJdjn8R+us/JWDE9RpcZMye35YbmSf\n\
vEtSfCk2YusD8KiS/FrB+H577YHMlt8CcoPOWRhzoZzPHApGSblc3X+6SnGmcXKM\n\
qewdgAS3sjoJv+DJK/p6n4dY8sI3EryDNDEZsam/jwa+/+k0F9qF7mZc+9ms+DAv\n\
dAtwUsXFHy3afmmt4XF7SJbg5GW+OFY7Mn1tIJEMw4RUiAYTJnD6u9NRi7nNitik\n\
R5y/w4ECgYEA6D/wDxFJFXeV+D0FIgj53hjY2qsELQMMcIHfeCVV4XK/Sr2meC3H\n\
ey/nCP6ybS+Ls6LBhDPC1Pa0AwTbge0CYnS4NRLl3rXc6jjNVEIIUADPY0SFhHUd\n\
uuhnhd72EvwL1XNYxGjCtQ9kUccrvQKGduUomPjQ6OJVvP3vZNZCXQMCgYEAwJO+\n\
ILkA+LzDLF0KtKIlLrqNQn4gmZXG0NoMH9ZWtMebspCmfH3RAZIhS6/aryA3eWsv\n\
8dunePlqLJMYCgv6BOdTOieLAS2ecuYfzOOfOPNRVLfhONQ/XIwtJVBDLiJVR7Ae\n\
Ap1BDtwibp9HfNxN94mr3qI2NVmCYPw8SMuliyECgYEAlwMD33g40hmIzPk4PjIh\n\
7hSv5DbwpyflTb5UhLWaCtZmpX19IYV6wJGcItAhSjdxGeOI+qIBXCHxWEkvRWLL\n\
eyMzp2bbSp1rwGwgrlmlOAfe0Uf7nO3d3+s/bN9Vl3CFbUvr+wG3IK2aaEYeHW7n\n\
6aUFabnXdKW+Y/2lTCa4zesCgYAAwhQjiNbqI8QY7pzWLTU8Q9u+gUSbli1cMR+P\n\
GIbq20ZPo6YkI1KpUOv0olKYEeZmAfgEWbsFDOZQGpwjnfxz/H0lY3Z2oLlY9nL1\n\
mYfM75hIXxjx4lQFhz++P9yj19rCF31mwTu6VT+Fc/cSFMPxz4bvr2/LMfkDbLrI\n\
BpU2QQKBgHRp9T9JQMomOFXnNSGqo8c/Uaoh+YprN8xJTvEJ6R5nyp5rgxeDbCvF\n\
V0Cacp04PlSke6ak0EI0SwOKJr5hIPobzqKNfVOjodkaZl6p+G9Oo+/5Vs2OEZKU\n\
RZnXlnXIF520ZNI1rQCezG9ff9tR3cuLhnE48LXuAyA91cQiQm0x\n\
-----END RSA PRIVATE KEY-----\n"};


#ifdef __cplusplus
}
#endif
