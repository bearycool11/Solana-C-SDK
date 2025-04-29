import hashlib
from pathlib import Path

# Insert the simulation code from earlier...
# (FeeCalculator, BugWatcher, BurnBlock, LedgerSim definitions)

def run_simulation(slot, fee_events):
    ledger = LedgerSim()
    fc = FeeCalculator(5000, 0.5)
    bb = BurnBlock(slot, fc)
    for account, lamports in fee_events:
        bb.record_fee(account, lamports)
    bb.execute(ledger)
    kindling = hashlib.sha256(slot.to_bytes(8, 'little')).hexdigest()
    torching = hashlib.sha256(bb.burned_total.to_bytes(8, 'little')).hexdigest()
    ledger.log(f"KINDLING: {kindling}")
    ledger.log(f"TORCHING: {torching}")
    return ledger.show()

# Example
result = run_simulation(12345, [
    (0x1, 15000),   # normal
    (0x2, 5000),    # owner mismatch
    (0x3, 2**64)    # overflow
])
print("Logs:", *result["logs"], sep="\n")
print("Rewards:", result["rewards"])o
