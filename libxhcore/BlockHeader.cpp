/// ethminer -- Ethereum miner with OpenCL, CUDA and stratum support.
/// Copyright 2018 ethminer Authors.
/// Licensed under GNU General Public License, Version 3. See the LICENSE file.

#include "BlockHeader.h"

#include <libdevcore/Common.h>
#include <libdevcore/RLP.h>

#include <ethash/keccak.hpp>

namespace dev
{
namespace eth
{
h256 const& BlockHeader::boundary() const
{
    if (!m_boundary && m_difficulty)
        m_boundary = (h256)(u256)((bigint(1) << 256) / m_difficulty);
    return m_boundary;
}

h256 const& BlockHeader::hashWithout() const
{
    if (!m_hashWithout)
    {
        RLPStream s(BasicFields);
        streamRLPFields(s);
        const bytes& rlp = s.out();
        auto hash = ethash::keccak256(rlp.data(), rlp.size());
        m_hashWithout = h256{hash.bytes, h256::ConstructFromPointer};
    }
    return m_hashWithout;
}

void BlockHeader::streamRLPFields(RLPStream& _s) const
{
    _s << m_parentHash << m_sha3Uncles << m_coinbaseAddress << m_stateRoot << m_transactionsRoot
       << m_receiptsRoot << m_logBloom << m_difficulty << m_number << m_gasLimit << m_gasUsed
       << m_timestamp << m_extraData;
}
}  // namespace eth
}  // namespace dev
