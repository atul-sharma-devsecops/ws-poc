// SPDX-License-Identifier: BSD-3-Clause
/**
 * @file test-plugin.h
 *
 * @brief mptcpd plugin test header.
 *
 * Copyright (c) 2019, 2020, Intel Corporation
 */

#ifndef MPTCPD_TEST_PLUGIN_H
#define MPTCPD_TEST_PLUGIN_H

#include <stdbool.h>

#include <netinet/in.h>

#include <mptcpd/types.h>


#ifdef __cplusplus
extern "C" {
#endif

// ------------------------------------------------------------------

/**
 * @struct plugin_call_count
 *
 * @brief Plugin operation call counts.
 *
 * The structure is used to track the number of times each mptcpd
 * plugin operation is called or should be called.
 */
struct plugin_call_count
{
        /**
         * @name Mptcpd Plugin Operation Call Counts
         *
         * Each of these fields corresponds to the callback operations
         * defined in @c mptcpd_plugin_ops that all mptcpd plugins
         * must implement.
         */
        ///@{
        int new_connection;
        int connection_established;
        int connection_closed;
        int new_address;
        int address_removed;
        int new_subflow;
        int subflow_closed;
        int subflow_priority;
        ///@}
};

/**
 * @brief Reset plugin operation call counts.
 */
void call_count_reset(struct plugin_call_count *p);

/**
 * @brief Check if all plugin operation call counts are not negative.
 */
bool call_count_all_positive(struct plugin_call_count const *p);

/**
 * @brief Perform a sanity check on the plugin operation call counts.
 */
bool call_count_is_sane(struct plugin_call_count const *p);

/**
 * @brief Compare plugin operation call counts for equality.
 */
bool call_count_is_equal(struct plugin_call_count const *lhs,
                         struct plugin_call_count const *rhs);

// ------------------------------------------------------------------

/**
 * @name Plugin Operation Call Signatures
 *
 * Each test plugin will be called with a specific set of operations,
 * i.e. a "call signature", to verify that only the operations we
 * intended to call were actually called.
 */
///@{
static struct plugin_call_count const test_count_1 = {
        .new_connection         = 1,
        .connection_established = 1,
        .connection_closed      = 1,
        .new_address            = 1,
        .address_removed        = 0,
        .new_subflow            = 0,
        .subflow_closed         = 0,
        .subflow_priority       = 0
};

static struct plugin_call_count const test_count_2 = {
        .new_connection         = 1,
        .connection_established = 1,
        .connection_closed      = 1,
        .new_address            = 0,
        .address_removed        = 1,
        .new_subflow            = 1,
        .subflow_closed         = 1,
        .subflow_priority       = 1
};

static struct plugin_call_count const test_count_4 = {
        .new_connection         = 1,
        .connection_established = 1,
        .connection_closed      = 1,
        .new_address            = 1,
        .address_removed        = 1,
        .new_subflow            = 0,
        .subflow_closed         = 0,
        .subflow_priority       = 0
};
///@}

// ------------------------------------------------------------------

/**
 * @name Plugin Operation Argument Test Values
 *
 * Arbitrary test values passed to test plugin operations.  We only
 * care about matching values, not if they are actually valid for the
 * types of values they correspond to.
 */
///@{
static mptcpd_token_t const test_token_1    = 0x12345678;
static mptcpd_aid_t   const test_laddr_id_1 = 0x34;
static mptcpd_aid_t   const test_raddr_id_1 = 0x56;
static bool           const test_backup_1   = true;

static mptcpd_token_t const test_token_2    = 0x23456789;
static mptcpd_aid_t   const test_laddr_id_2 = 0x23;
static mptcpd_aid_t   const test_raddr_id_2 = 0x45;
static bool           const test_backup_2   = false;

static mptcpd_token_t const test_token_4    = 0x34567890;
static mptcpd_aid_t   const test_laddr_id_4 = 0x90;
static mptcpd_aid_t   const test_raddr_id_4 = 0x01;
static bool           const test_backup_4   = true;

// For verifying that a plugin will not be dispatched.
static mptcpd_token_t const test_bad_token  = 0xFFFFFFFF;

/*
  Mptcpd Test IP Address Notes
  ============================
  IPv4 addresses conform to IETF RFC 5737: IPv4 Address Blocks
  Reserved for Documentation.

  IPv6 addresses conform to IETF RFC 3849: IPv6 Address Prefix
  Reserved for Documentation.
 */
static struct sockaddr_in const test_laddr_1 = {
        .sin_family = AF_INET,
        .sin_port   = 0x1234,
        .sin_addr   = { .s_addr = 0x010200C0 }  // 192.0.2.1
};

#ifdef __cplusplus
/*
  s6_addr is a macro that expands to code that isn't compatible with
  g++'s minimal support for C99 designated initializers.  Use IPv4
  address instead.
*/
static struct sockaddr_in const test_laddr_2 = {
        .sin_family = AF_INET,
        .sin_port   = 0x5678,
        .sin_addr   = { .s_addr = 0x020200C0 }  // 192.0.2.2
};
#else
static struct sockaddr_in6 const test_laddr_2 = {
        .sin6_family = AF_INET6,
        .sin6_port   = 0x5678,
        .sin6_addr   = { .s6_addr = { [0]  = 0x20,
                                      [1]  = 0x01,
                                      [2]  = 0X0D,
                                      [3]  = 0xB8,
                                      [14] = 0x01,
                                      [15] = 0x02 }  // 2001:DB8::102
        }
};
#endif  // __cplusplus


#ifdef __cplusplus
/*
  s6_addr is a macro that expands to code that isn't compatible with
  g++'s minimal support for C99 designated initializers.  Use IPv4
  address instead.
*/
static struct sockaddr_in const test_raddr_1 = {
        .sin_family = AF_INET,
        .sin_port   = 0x3456,
        .sin_addr   = { .s_addr = 0x017100CB }  // 203.0.113.1
};
#else
static struct sockaddr_in6 const test_raddr_1 = {
        .sin6_family = AF_INET6,
        .sin6_port   = 0x3456,
        .sin6_addr   = { .s6_addr = { [0]  = 0x20,
                                      [1]  = 0x01,
                                      [2]  = 0X0D,
                                      [3]  = 0xB8,
                                      [14] = 0x02,
                                      [15] = 0x01 }  // 2001:DB8::201
        }
};
#endif  // __cplusplus

static struct sockaddr_in const test_raddr_2 = {
        .sin_family = AF_INET,
        .sin_port   = 0x7890,
        .sin_addr   = { .s_addr = 0x027100CB }  // 203.0.113.2
};

static struct sockaddr_in const test_laddr_4 = {
        .sin_family = AF_INET,
        .sin_port   = 0x2345,
        .sin_addr   = { .s_addr = 0x040200C0 }  // 192.0.2.4
};

static struct sockaddr_in const test_raddr_4 = {
        .sin_family = AF_INET,
        .sin_port   = 0x3456,
        .sin_addr   = { .s_addr = 0x047100CB }  // 203.0.113.4
};

///@}

/**
 * @brief Compare equality of two @c sockaddr objects.
 *
 * @return @c true if both @c sockaddr objects are equal. @c false
 *         otherwise.
 */
bool sockaddr_is_equal(struct sockaddr const *lhs,
                       struct sockaddr const *rhs);

/**
 * @brief Call plugin operations
 *
 * @param[in] count    Number of times to call each plugin operation.
 * @param[in] name     Plugin name.
 * @param[in] raddr_id Remote address ID.
 * @param[in] laddr    Local address.
 * @param[in] raddr    Remote address.
 * @param[in] backup   MPTCP backup priority.
 */
void call_plugin_ops(struct plugin_call_count const *count,
                     char const *name,
                     mptcpd_token_t token,
                     mptcpd_aid_t raddr_id,
                     struct sockaddr const *laddr,
                     struct sockaddr const *raddr,
                     bool backup);


#ifdef __cplusplus
}
#endif

#endif /* MPTCPD_TEST_PLUGIN_H */

/*
  Local Variables:
  c-file-style: "linux"
  End:
*/
