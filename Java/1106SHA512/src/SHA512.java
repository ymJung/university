import java.security.*;
import java.util.*;

public class SHA512 extends MessageDigest implements Cloneable {
    private long bytes;
    private int padded;
    private byte[] pad;
    private long hA, hB, hC, hD, hE, hF, hG, hH;
    private long m0, m1, m2, m3, m4, m5, m6, m7,
                 m8, m9, mA, mB, mC, mD, mE, mF;
    private long tA, tB, tC, tD, tE, tF, tG, tH;
    public SHA512() {
        super("SHA-512");
        pad = new byte[128];
        init();
    }
    public Object clone() throws CloneNotSupportedException  {
        SHA512 that = (SHA512)super.clone();
        that.pad = (byte[])this.pad.clone();
        return that;
    }
    public void engineReset() {
        int offset = 124;
        do {
           pad[offset + 3] = pad[offset + 2] =
           pad[offset + 1] = pad[offset    ] =
           pad[offset - 1] = pad[offset - 2] =
           pad[offset - 3] = pad[offset - 4] = (byte)0x00;
        } while ((offset -= 8) >= 0);
        padded = 0;
        bytes =
        m0 = m1 = m2 = m3 = m4 = m5 = m6 = m7 =
        m8 = m9 = mA = mB = mC = mD = mE = mF =
        tA = tB = tC = tD = tE = tF = tG = tH = 0L;
        init();
    }
    protected void init() {
        hA = 0x6a09e667f3bcc908L;
        hB = 0xbb67ae8584caa73bL;
        hC = 0x3c6ef372fe94f82bL;
        hD = 0xa54ff53a5f1d36f1L;
        hE = 0x510e527fade682d1L;
        hF = 0x9b05688c2b3e6c1fL;
        hG = 0x1f83d9abfb41bd6bL;
        hH = 0x5be0cd19137e2179L;
    }
    public void engineUpdate(byte input) {
        bytes++;
        if (padded < 127) {
            pad[padded++] = input;
            return;
        }
        pad[127] = input;
        transformBlock(pad, padded = 0);
        computeBlock();
    }
    public void engineUpdate(byte[] input, int offset, int length) {
        if (offset >= 0 && length >= 0 && offset + length <= input.length) {
            bytes += length;
            if (padded > 0 && padded + length >= 128) {
                final int remaining;
                System.arraycopy(input, offset, pad, padded,
                    remaining = 128 - padded);
                transformBlock(pad, padded = 0);
                computeBlock();
                offset += remaining;
                length -= remaining;
            }
            while (length >= 1024) {
                transformBlock(input, offset);
                computeBlock();
                transformBlock(input, offset + 128);
                computeBlock();
                transformBlock(input, offset + 256);
                computeBlock();
                transformBlock(input, offset + 384);
                computeBlock();
                transformBlock(input, offset + 512);
                computeBlock();
                transformBlock(input, offset + 640);
                computeBlock();
                transformBlock(input, offset + 768);
                computeBlock();
                transformBlock(input, offset + 896);
                computeBlock();
                offset += 1024;
                length -= 1024;
            }
            while (length >= 128) {
                transformBlock(input, offset);
                computeBlock();
                offset += 128;
                length -= 128;
            }
            if (length > 0) {
                System.arraycopy(input, offset, pad, padded, length);
                padded += length;
            }
            return;
        }
        throw new ArrayIndexOutOfBoundsException(offset);
    }
    public byte[] engineDigest() {
        try {
            final byte hashvalue[] = new byte[64]; /* digest length in bytes */
            engineDigest(hashvalue, 0, 64); /* digest length in bytes */
            return hashvalue;
        } catch (DigestException e) {
            return null;
        }
    }

    public int engineGetDigestLength() {
        return 64; /* digest length in bytes */
    }
    public int engineDigest(byte[] hashvalue, int offset, final int length)
            throws DigestException {
        if (length >= 64) { /* digest length in bytes */
            if (hashvalue.length - offset >= 64) { /* digest length in bytes */
                int i;
                pad[i = padded] = (byte)0x80; /* required 1st padded byte */
                switch (i) { /* INVARIANT: m0 must be in [0..127] */
                case 112: pad[113] = (byte)0x00; /* no break; falls thru */
                case 113: pad[114] = (byte)0x00; /* no break; falls thru */
                case 114: pad[115] = (byte)0x00; /* no break; falls thru */
                case 115: pad[116] = (byte)0x00; /* no break; falls thru */
                case 116: pad[117] = (byte)0x00; /* no break; falls thru */
                case 117: pad[118] = (byte)0x00; /* no break; falls thru */
                case 118: pad[119] = (byte)0x00; /* no break; falls thru */
                case 119: pad[120] = (byte)0x00; /* no break; falls thru */
                case 120: pad[121] = (byte)0x00; /* no break; falls thru */
                case 121: pad[122] = (byte)0x00; /* no break; falls thru */
                case 122: pad[123] = (byte)0x00; /* no break; falls thru */
                case 123: pad[124] = (byte)0x00; /* no break; falls thru */
                case 124: pad[125] = (byte)0x00; /* no break; falls thru */
                case 125: pad[126] = (byte)0x00; /* no break; falls thru */
                case 126: pad[127] = (byte)0x00; /* no break; falls thru */
                case 127:
                    transformBlock(pad, 0);
                    computeBlock();
                    m0 = m1 = m2 = m3 = m4 = m5 = m6 = m7 =
                    m8 = m9 = mA = mB = mC = mD = 0L;
                    mE = bytes >>> 61;
                    mF = bytes << 3;
                    computeBlock();
                    break;
                default:
                    switch (i & 7) {
                    case 7:      i-=3;
                            break;
                    case 6: pad[(i-=2)+3] = (byte)0x00;
                            break;
                    case 5: pad[(i-=1)+3] = pad[i+2] = (byte)0x00;
                            break;
                    case 4: pad[i+3] = pad[i+2] = pad[i+1] = (byte)0x00;
                            break;
                    case 3: pad[(i+=1)+3] = pad[i+2] = pad[i+1] = pad[i] =
                            (byte)0x00;
                            break;
                    case 2: pad[(i+=2)+3] = pad[i+2] = pad[i+1] = pad[i] =
                            pad[i-1] = (byte)0x00;
                            break;
                    case 1: pad[(i+=3)+3] = pad[i+2] = pad[i+1] = pad[i] =
                            pad[i-1] = pad[i-2] = (byte)0x00;
                            break;
                    case 0: pad[(i+=4)+3] = pad[i+2] = pad[i+1] = pad[i] =
                            pad[i-1] = pad[i-2] = pad[i-3] = (byte)0x00;
                            break;
                    }
                    while ((i += 8) < 116) {
                        pad[i+3] = pad[i+2] = pad[i+1] = pad[i] = pad[i-1] =
                        pad[i-2] = pad[i-3] = pad[i-4] = (byte)0x00;
                    }
                    transformPadLength();
                    computeBlock();
                }
                hashvalue[ offset       ] = (byte)((i = (int)(hA >>> 32)) >>> 24);
                hashvalue[ offset     +1] = (byte)(i >>> 16);
                hashvalue[ offset     +2] = (byte)(i >>> 8);
                hashvalue[ offset     +3] = (byte)i;
                hashvalue[ offset     +4] = (byte)((i = (int)hA) >>> 24);
                hashvalue[ offset     +5] = (byte)(i >>> 16);
                hashvalue[(offset+=10)-4] = (byte)(i >>> 8);
                hashvalue[ offset     -3] = (byte)i;
                hashvalue[ offset     -2] = (byte)((i = (int)(hB >>> 32)) >>> 24);
                hashvalue[ offset     -1] = (byte)(i >>> 16);
                hashvalue[ offset       ] = (byte)(i >>> 8);
                hashvalue[ offset     +1] = (byte)i;
                hashvalue[ offset     +2] = (byte)((i = (int)hB) >>> 24);
                hashvalue[ offset     +3] = (byte)(i >>> 16);
                hashvalue[ offset     +4] = (byte)(i >>> 8);
                hashvalue[ offset     +5] = (byte)i;
                hashvalue[(offset+=10)-4] = (byte)((i = (int)(hC >>> 32)) >>> 24);
                hashvalue[ offset     -3] = (byte)(i >>> 16);
                hashvalue[ offset     -2] = (byte)(i >>> 8);
                hashvalue[ offset     -1] = (byte)i;
                hashvalue[ offset       ] = (byte)((i = (int)hC) >>> 24);
                hashvalue[ offset     +1] = (byte)(i >>> 16);
                hashvalue[ offset     +2] = (byte)(i >>> 8);
                hashvalue[ offset     +3] = (byte)i;
                hashvalue[ offset     +4] = (byte)((i = (int)(hD >>> 32)) >>> 24);
                hashvalue[ offset     +5] = (byte)(i >>> 16);
                hashvalue[(offset+=10)-4] = (byte)(i >>> 8);
                hashvalue[ offset     -3] = (byte)i;
                hashvalue[ offset     -2] = (byte)((i = (int)hD) >>> 24);
                hashvalue[ offset     -1] = (byte)(i >>> 16);
                hashvalue[ offset       ] = (byte)(i >>> 8);
                hashvalue[ offset     +1] = (byte)i;
                hashvalue[ offset     +2] = (byte)((i = (int)(hE >>> 32)) >>> 24);
                hashvalue[ offset     +3] = (byte)(i >>> 16);
                hashvalue[ offset     +4] = (byte)(i >>> 8);
                hashvalue[ offset     +5] = (byte)i;
                hashvalue[(offset+=10)-4] = (byte)((i = (int)hE) >>> 24);
                hashvalue[ offset     -3] = (byte)(i >>> 16);
                hashvalue[ offset     -2] = (byte)(i >>> 8);
                hashvalue[ offset     -1] = (byte)i;
                hashvalue[ offset       ] = (byte)((i = (int)(hF >>> 32)) >>> 24);
                hashvalue[ offset     +1] = (byte)(i >>> 16);
                hashvalue[ offset     +2] = (byte)(i >>> 8);
                hashvalue[ offset     +3] = (byte)i;
                hashvalue[ offset     +4] = (byte)((i = (int)hF) >>> 24);
                hashvalue[ offset     +5] = (byte)(i >>> 16);
                hashvalue[(offset+=10)-4] = (byte)(i >>> 8);
                hashvalue[ offset     -3] = (byte)i;
                hashvalue[ offset     -2] = (byte)((i = (int)(hG >>> 32)) >>> 24);
                hashvalue[ offset     -1] = (byte)(i >>> 16);
                hashvalue[ offset       ] = (byte)(i >>> 8);
                hashvalue[ offset     +1] = (byte)i;
                hashvalue[ offset     +2] = (byte)((i = (int)hG) >>> 24);
                hashvalue[ offset     +3] = (byte)(i >>> 16);
                hashvalue[ offset     +4] = (byte)(i >>> 8);
                hashvalue[ offset     +5] = (byte)i;
                hashvalue[(offset+=10)-4] = (byte)((i = (int)(hH >>> 32)) >>> 24);
                hashvalue[ offset     -3] = (byte)(i >>> 16);
                hashvalue[ offset     -2] = (byte)(i >>> 8);
                hashvalue[ offset     -1] = (byte)i;
                hashvalue[ offset       ] = (byte)((i = (int)hH) >>> 24);
                hashvalue[ offset     +1] = (byte)(i >>> 16);
                hashvalue[ offset     +2] = (byte)(i >>> 8);
                hashvalue[ offset     +3] = (byte)i;
                engineReset(); /* clear the evidence */
                return 64; /* digest length in bytes */
            }
            throw new DigestException(
                "insufficient space in output buffer to store the digest");
        }
        throw new DigestException("partial digests not returned");
    }

    private final void transformPadLength() {
        final byte[] input = pad;
        int offset;

        m0 = ((long)(  input[        0] << 24
                    | (input[        1] & 0xff) << 16
                    | (input[        2] & 0xff) << 8
                    | (input[        3] & 0xff)) << 32) |
             ((long)(  input[        4] << 24
                    | (input[        5] & 0xff) << 16
                    | (input[(offset =10)-4] & 0xff) << 8
                    | (input[ offset     -3] & 0xff)) & 0xffffffffL); /* W00 */
        m1 = ((long)(  input[ offset     -2] << 24
                    | (input[ offset     -1] & 0xff) << 16
                    | (input[ offset       ] & 0xff) << 8
                    | (input[ offset     +1] & 0xff)) << 32) |
             ((long)(  input[ offset     +2] << 24
                    | (input[ offset     +3] & 0xff) << 16
                    | (input[ offset     +4] & 0xff) << 8
                    | (input[ offset     +5] & 0xff)) & 0xffffffffL); /* W01 */
        m2 = ((long)(  input[(offset+=10)-4] << 24
                    | (input[ offset     -3] & 0xff) << 16
                    | (input[ offset     -2] & 0xff) << 8
                    | (input[ offset     -1] & 0xff)) << 32) |
             ((long)(  input[ offset       ] << 24
                    | (input[ offset     +1] & 0xff) << 16
                    | (input[ offset     +2] & 0xff) << 8
                    | (input[ offset     +3] & 0xff)) & 0xffffffffL); /* W02 */
        m3 = ((long)(  input[ offset     +4] << 24
                    | (input[ offset     +5] & 0xff) << 16
                    | (input[(offset+=10)-4] & 0xff) << 8
                    | (input[ offset     -3] & 0xff)) << 32) |
             ((long)(  input[ offset     -2] << 24
                    | (input[ offset     -1] & 0xff) << 16
                    | (input[ offset       ] & 0xff) << 8
                    | (input[ offset     +1] & 0xff)) & 0xffffffffL); /* W03 */
        m4 = ((long)(  input[ offset     +2] << 24
                    | (input[ offset     +3] & 0xff) << 16
                    | (input[ offset     +4] & 0xff) << 8
                    | (input[ offset     +5] & 0xff)) << 32) |
             ((long)(  input[(offset+=10)-4] << 24
                    | (input[ offset     -3] & 0xff) << 16
                    | (input[ offset     -2] & 0xff) << 8
                    | (input[ offset     -1] & 0xff)) & 0xffffffffL); /* W04 */
        m5 = ((long)(  input[ offset       ] << 24
                    | (input[ offset     +1] & 0xff) << 16
                    | (input[ offset     +2] & 0xff) << 8
                    | (input[ offset     +3] & 0xff)) << 32) |
             ((long)(  input[ offset     +4] << 24
                    | (input[ offset     +5] & 0xff) << 16
                    | (input[(offset+=10)-4] & 0xff) << 8
                    | (input[ offset     -3] & 0xff)) & 0xffffffffL); /* W05 */
        m6 = ((long)(  input[ offset     -2] << 24
                    | (input[ offset     -1] & 0xff) << 16
                    | (input[ offset       ] & 0xff) << 8
                    | (input[ offset     +1] & 0xff)) << 32) |
             ((long)(  input[ offset     +2] << 24
                    | (input[ offset     +3] & 0xff) << 16
                    | (input[ offset     +4] & 0xff) << 8
                    | (input[ offset     +5] & 0xff)) & 0xffffffffL); /* W06 */
        m7 = ((long)(  input[(offset+=10)-4] << 24
                    | (input[ offset     -3] & 0xff) << 16
                    | (input[ offset     -2] & 0xff) << 8
                    | (input[ offset     -1] & 0xff)) << 32) |
             ((long)(  input[ offset       ] << 24
                    | (input[ offset     +1] & 0xff) << 16
                    | (input[ offset     +2] & 0xff) << 8
                    | (input[ offset     +3] & 0xff)) & 0xffffffffL); /* W07 */
        m8 = ((long)(  input[ offset     +4] << 24
                    | (input[ offset     +5] & 0xff) << 16
                    | (input[(offset+=10)-4] & 0xff) << 8
                    | (input[ offset     -3] & 0xff)) << 32) |
             ((long)(  input[ offset     -2] << 24
                    | (input[ offset     -1] & 0xff) << 16
                    | (input[ offset       ] & 0xff) << 8
                    | (input[ offset     +1] & 0xff)) & 0xffffffffL); /* W08 */
        m9 = ((long)(  input[ offset     +2] << 24
                    | (input[ offset     +3] & 0xff) << 16
                    | (input[ offset     +4] & 0xff) << 8
                    | (input[ offset     +5] & 0xff)) << 32) |
             ((long)(  input[(offset+=10)-4] << 24
                    | (input[ offset     -3] & 0xff) << 16
                    | (input[ offset     -2] & 0xff) << 8
                    | (input[ offset     -1] & 0xff)) & 0xffffffffL); /* W09 */
        mA = ((long)(  input[ offset       ] << 24
                    | (input[ offset     +1] & 0xff) << 16
                    | (input[ offset     +2] & 0xff) << 8
                    | (input[ offset     +3] & 0xff)) << 32) |
             ((long)(  input[ offset     +4] << 24
                    | (input[ offset     +5] & 0xff) << 16
                    | (input[(offset+=10)-4] & 0xff) << 8
                    | (input[ offset     -3] & 0xff)) & 0xffffffffL); /* W10 */
        mB = ((long)(  input[ offset     -2] << 24
                    | (input[ offset     -1] & 0xff) << 16
                    | (input[ offset       ] & 0xff) << 8
                    | (input[ offset     +1] & 0xff)) << 32) |
             ((long)(  input[ offset     +2] << 24
                    | (input[ offset     +3] & 0xff) << 16
                    | (input[ offset     +4] & 0xff) << 8
                    | (input[ offset     +5] & 0xff)) & 0xffffffffL); /* W11 */
        mC = ((long)(  input[(offset+=10)-4] << 24
                    | (input[ offset     -3] & 0xff) << 16
                    | (input[ offset     -2] & 0xff) << 8
                    | (input[ offset     -1] & 0xff)) << 32) |
             ((long)(  input[ offset       ] << 24
                    | (input[ offset     +1] & 0xff) << 16
                    | (input[ offset     +2] & 0xff) << 8
                    | (input[ offset     +3] & 0xff)) & 0xffffffffL); /* W12 */
        mD = ((long)(  input[ offset     +4] << 24
                    | (input[ offset     +5] & 0xff) << 16
                    | (input[(offset+=10)-4] & 0xff) << 8
                    | (input[ offset     -3] & 0xff)) << 32) |
             ((long)(  input[ offset     -2] << 24
                    | (input[ offset     -1] & 0xff) << 16
                    | (input[ offset       ] & 0xff) << 8
                    | (input[ offset     +1] & 0xff)) & 0xffffffffL); /* W13 */
        mE = bytes >>> 61;
        mF = bytes << 3;
    }

    private final void transformBlock(final byte[] input, int offset) {
        m0 = ((long)(  input[ offset       ] << 24
                    | (input[ offset     +1] & 0xff) << 16
                    | (input[ offset     +2] & 0xff) << 8
                    | (input[ offset     +3] & 0xff)) << 32) |
             ((long)(  input[ offset     +4] << 24
                    | (input[ offset     +5] & 0xff) << 16
                    | (input[(offset+=10)-4] & 0xff) << 8
                    | (input[ offset     -3] & 0xff)) & 0xffffffffL); /* W00 */
        m1 = ((long)(  input[ offset     -2] << 24
                    | (input[ offset     -1] & 0xff) << 16
                    | (input[ offset       ] & 0xff) << 8
                    | (input[ offset     +1] & 0xff)) << 32) |
             ((long)(  input[ offset     +2] << 24
                    | (input[ offset     +3] & 0xff) << 16
                    | (input[ offset     +4] & 0xff) << 8
                    | (input[ offset     +5] & 0xff)) & 0xffffffffL); /* W01 */
        m2 = ((long)(  input[(offset+=10)-4] << 24
                    | (input[ offset     -3] & 0xff) << 16
                    | (input[ offset     -2] & 0xff) << 8
                    | (input[ offset     -1] & 0xff)) << 32) |
             ((long)(  input[ offset       ] << 24
                    | (input[ offset     +1] & 0xff) << 16
                    | (input[ offset     +2] & 0xff) << 8
                    | (input[ offset     +3] & 0xff)) & 0xffffffffL); /* W02 */
        m3 = ((long)(  input[ offset     +4] << 24
                    | (input[ offset     +5] & 0xff) << 16
                    | (input[(offset+=10)-4] & 0xff) << 8
                    | (input[ offset     -3] & 0xff)) << 32) |
             ((long)(  input[ offset     -2] << 24
                    | (input[ offset     -1] & 0xff) << 16
                    | (input[ offset       ] & 0xff) << 8
                    | (input[ offset     +1] & 0xff)) & 0xffffffffL); /* W03 */
        m4 = ((long)(  input[ offset     +2] << 24
                    | (input[ offset     +3] & 0xff) << 16
                    | (input[ offset     +4] & 0xff) << 8
                    | (input[ offset     +5] & 0xff)) << 32) |
             ((long)(  input[(offset+=10)-4] << 24
                    | (input[ offset     -3] & 0xff) << 16
                    | (input[ offset     -2] & 0xff) << 8
                    | (input[ offset     -1] & 0xff)) & 0xffffffffL); /* W04 */
        m5 = ((long)(  input[ offset       ] << 24
                    | (input[ offset     +1] & 0xff) << 16
                    | (input[ offset     +2] & 0xff) << 8
                    | (input[ offset     +3] & 0xff)) << 32) |
             ((long)(  input[ offset     +4] << 24
                    | (input[ offset     +5] & 0xff) << 16
                    | (input[(offset+=10)-4] & 0xff) << 8
                    | (input[ offset     -3] & 0xff)) & 0xffffffffL); /* W05 */
        m6 = ((long)(  input[ offset     -2] << 24
                    | (input[ offset     -1] & 0xff) << 16
                    | (input[ offset       ] & 0xff) << 8
                    | (input[ offset     +1] & 0xff)) << 32) |
             ((long)(  input[ offset     +2] << 24
                    | (input[ offset     +3] & 0xff) << 16
                    | (input[ offset     +4] & 0xff) << 8
                    | (input[ offset     +5] & 0xff)) & 0xffffffffL); /* W06 */
        m7 = ((long)(  input[(offset+=10)-4] << 24
                    | (input[ offset     -3] & 0xff) << 16
                    | (input[ offset     -2] & 0xff) << 8
                    | (input[ offset     -1] & 0xff)) << 32) |
             ((long)(  input[ offset       ] << 24
                    | (input[ offset     +1] & 0xff) << 16
                    | (input[ offset     +2] & 0xff) << 8
                    | (input[ offset     +3] & 0xff)) & 0xffffffffL); /* W07 */
        m8 = ((long)(  input[ offset     +4] << 24
                    | (input[ offset     +5] & 0xff) << 16
                    | (input[(offset+=10)-4] & 0xff) << 8
                    | (input[ offset     -3] & 0xff)) << 32) |
             ((long)(  input[ offset     -2] << 24
                    | (input[ offset     -1] & 0xff) << 16
                    | (input[ offset       ] & 0xff) << 8
                    | (input[ offset     +1] & 0xff)) & 0xffffffffL); /* W08 */
        m9 = ((long)(  input[ offset     +2] << 24
                    | (input[ offset     +3] & 0xff) << 16
                    | (input[ offset     +4] & 0xff) << 8
                    | (input[ offset     +5] & 0xff)) << 32) |
             ((long)(  input[(offset+=10)-4] << 24
                    | (input[ offset     -3] & 0xff) << 16
                    | (input[ offset     -2] & 0xff) << 8
                    | (input[ offset     -1] & 0xff)) & 0xffffffffL); /* W09 */
        mA = ((long)(  input[ offset       ] << 24
                    | (input[ offset     +1] & 0xff) << 16
                    | (input[ offset     +2] & 0xff) << 8
                    | (input[ offset     +3] & 0xff)) << 32) |
             ((long)(  input[ offset     +4] << 24
                    | (input[ offset     +5] & 0xff) << 16
                    | (input[(offset+=10)-4] & 0xff) << 8
                    | (input[ offset     -3] & 0xff)) & 0xffffffffL); /* W10 */
        mB = ((long)(  input[ offset     -2] << 24
                    | (input[ offset     -1] & 0xff) << 16
                    | (input[ offset       ] & 0xff) << 8
                    | (input[ offset     +1] & 0xff)) << 32) |
             ((long)(  input[ offset     +2] << 24
                    | (input[ offset     +3] & 0xff) << 16
                    | (input[ offset     +4] & 0xff) << 8
                    | (input[ offset     +5] & 0xff)) & 0xffffffffL); /* W11 */
        mC = ((long)(  input[(offset+=10)-4] << 24
                    | (input[ offset     -3] & 0xff) << 16
                    | (input[ offset     -2] & 0xff) << 8
                    | (input[ offset     -1] & 0xff)) << 32) |
             ((long)(  input[ offset       ] << 24
                    | (input[ offset     +1] & 0xff) << 16
                    | (input[ offset     +2] & 0xff) << 8
                    | (input[ offset     +3] & 0xff)) & 0xffffffffL); /* W12 */
        mD = ((long)(  input[ offset     +4] << 24
                    | (input[ offset     +5] & 0xff) << 16
                    | (input[(offset+=10)-4] & 0xff) << 8
                    | (input[ offset     -3] & 0xff)) << 32) |
             ((long)(  input[ offset     -2] << 24
                    | (input[ offset     -1] & 0xff) << 16
                    | (input[ offset       ] & 0xff) << 8
                    | (input[ offset     +1] & 0xff)) & 0xffffffffL); /* W13 */
        mE = ((long)(  input[ offset     +2] << 24
                    | (input[ offset     +3] & 0xff) << 16
                    | (input[ offset     +4] & 0xff) << 8
                    | (input[ offset     +5] & 0xff)) << 32) |
             ((long)(  input[(offset+=10)-4] << 24
                    | (input[ offset     -3] & 0xff) << 16
                    | (input[ offset     -2] & 0xff) << 8
                    | (input[ offset     -1] & 0xff)) & 0xffffffffL); /* W14 */
        mF = ((long)(  input[ offset       ] << 24
                    | (input[ offset     +1] & 0xff) << 16
                    | (input[ offset     +2] & 0xff) << 8
                    | (input[ offset     +3] & 0xff)) << 32) |
             ((long)(  input[ offset     +4] << 24
                    | (input[ offset     +5] & 0xff) << 16
                    | (input[ offset     +6] & 0xff) << 8
                    | (input[ offset     +7] & 0xff)) & 0xffffffffL); /* W15 */
    }
    private final void computeBlock() {
        computeRounds(hA, hB, hC, hD, hE, hF, hG, hH,
            0x428a2f98d728ae22L /* K00 */ + m0 /* W00 */,
            0x7137449123ef65cdL /* K01 */ + m1 /* W01 */,
            0xb5c0fbcfec4d3b2fL /* K02 */ + m2 /* W02 */,
            0xe9b5dba58189dbbcL /* K03 */ + m3 /* W03 */,
            0x3956c25bf348b538L /* K04 */ + m4 /* W04 */,
            0x59f111f1b605d019L /* K05 */ + m5 /* W05 */,
            0x923f82a4af194f9bL /* K06 */ + m6 /* W06 */,
            0xab1c5ed5da6d8118L /* K07 */ + m7 /* W07 */);
        computeRounds(tA, tB, tC, tD, tE, tF, tG, tH,
            0xd807aa98a3030242L /* K08 */ + m8 /* W08 */,
            0x12835b0145706fbeL /* K09 */ + m9 /* W09 */,
            0x243185be4ee4b28cL /* K10 */ + mA /* W10 */,
            0x550c7dc3d5ffb4e2L /* K11 */ + mB /* W11 */,
            0x72be5d74f27b896fL /* K12 */ + mC /* W12 */,
            0x80deb1fe3b1696b1L /* K13 */ + mD /* W13 */,
            0x9bdc06a725c71235L /* K14 */ + mE /* W14 */,
            0xc19bf174cf692694L /* K15 */ + mF /* W15 */);
        /* Pass 2 (rounds 16..31). */
        scheduleBlock();
        computeRounds(tA, tB, tC, tD, tE, tF, tG, tH,
            0xe49b69c19ef14ad2L /* K16 */ + m0 /* W16 */,
            0xefbe4786384f25e3L /* K17 */ + m1 /* W17 */,
            0x0fc19dc68b8cd5b5L /* K18 */ + m2 /* W18 */,
            0x240ca1cc77ac9c65L /* K19 */ + m3 /* W19 */,
            0x2de92c6f592b0275L /* K20 */ + m4 /* W20 */,
            0x4a7484aa6ea6e483L /* K21 */ + m5 /* W21 */,
            0x5cb0a9dcbd41fbd4L /* K22 */ + m6 /* W22 */,
            0x76f988da831153b5L /* K23 */ + m7 /* W23 */);
        computeRounds(tA, tB, tC, tD, tE, tF, tG, tH,
            0x983e5152ee66dfabL /* K24 */ + m8 /* W24 */,
            0xa831c66d2db43210L /* K25 */ + m9 /* W25 */,
            0xb00327c898fb213fL /* K26 */ + mA /* W26 */,
            0xbf597fc7beef0ee4L /* K27 */ + mB /* W27 */,
            0xc6e00bf33da88fc2L /* K28 */ + mC /* W28 */,
            0xd5a79147930aa725L /* K29 */ + mD /* W29 */,
            0x06ca6351e003826fL /* K30 */ + mE /* W30 */,
            0x142929670a0e6e70L /* K31 */ + mF /* W31 */);
        /* Pass 3 (rounds 32..47). */
        scheduleBlock();
        computeRounds(tA, tB, tC, tD, tE, tF, tG, tH,
            0x27b70a8546d22ffcL /* K32 */ + m0 /* W32 */,
            0x2e1b21385c26c926L /* K33 */ + m1 /* W33 */,
            0x4d2c6dfc5ac42aedL /* K34 */ + m2 /* W34 */,
            0x53380d139d95b3dfL /* K35 */ + m3 /* W35 */,
            0x650a73548baf63deL /* K36 */ + m4 /* W36 */,
            0x766a0abb3c77b2a8L /* K37 */ + m5 /* W37 */,
            0x81c2c92e47edaee6L /* K38 */ + m6 /* W38 */,
            0x92722c851482353bL /* K39 */ + m7 /* W39 */);
        computeRounds(tA, tB, tC, tD, tE, tF, tG, tH,
            0xa2bfe8a14cf10364L /* K40 */ + m8 /* W40 */,
            0xa81a664bbc423001L /* K41 */ + m9 /* W41 */,
            0xc24b8b70d0f89791L /* K42 */ + mA /* W42 */,
            0xc76c51a30654be30L /* K43 */ + mB /* W43 */,
            0xd192e819d6ef5218L /* K44 */ + mC /* W44 */,
            0xd69906245565a910L /* K45 */ + mD /* W45 */,
            0xf40e35855771202aL /* K46 */ + mE /* W46 */,
            0x106aa07032bbd1b8L /* K47 */ + mF /* W47 */);
        /* Pass 4 (rounds 48..63). */
        scheduleBlock();
        computeRounds(tA, tB, tC, tD, tE, tF, tG, tH,
            0x19a4c116b8d2d0c8L /* K48 */ + m0 /* W48 */,
            0x1e376c085141ab53L /* K49 */ + m1 /* W49 */,
            0x2748774cdf8eeb99L /* K50 */ + m2 /* W50 */,
            0x34b0bcb5e19b48a8L /* K51 */ + m3 /* W51 */,
            0x391c0cb3c5c95a63L /* K52 */ + m4 /* W52 */,
            0x4ed8aa4ae3418acbL /* K53 */ + m5 /* W53 */,
            0x5b9cca4f7763e373L /* K54 */ + m6 /* W54 */,
            0x682e6ff3d6b2b8a3L /* K55 */ + m7 /* W55 */);
        computeRounds(tA, tB, tC, tD, tE, tF, tG, tH,
            0x748f82ee5defb2fcL /* K56 */ + m8 /* W56 */,
            0x78a5636f43172f60L /* K57 */ + m9 /* W57 */,
            0x84c87814a1f0ab72L /* K58 */ + mA /* W58 */,
            0x8cc702081a6439ecL /* K59 */ + mB /* W59 */,
            0x90befffa23631e28L /* K60 */ + mC /* W60 */,
            0xa4506cebde82bde9L /* K61 */ + mD /* W61 */,
            0xbef9a3f7b2c67915L /* K62 */ + mE /* W62 */,
            0xc67178f2e372532bL /* K63 */ + mF /* W63 */);
        /* Pass 5 (rounds 64..79). */
        scheduleBlock();
        computeRounds(tA, tB, tC, tD, tE, tF, tG, tH,
            0xca273eceea26619cL /* K64 */ + m0 /* W64 */,
            0xd186b8c721c0c207L /* K65 */ + m1 /* W65 */,
            0xeada7dd6cde0eb1eL /* K66 */ + m2 /* W66 */,
            0xf57d4f7fee6ed178L /* K67 */ + m3 /* W67 */,
            0x06f067aa72176fbaL /* K68 */ + m4 /* W68 */,
            0x0a637dc5a2c898a6L /* K69 */ + m5 /* W69 */,
            0x113f9804bef90daeL /* K70 */ + m6 /* W70 */,
            0x1b710b35131c471bL /* K71 */ + m7 /* W71 */);
        computeRounds(tA, tB, tC, tD, tE, tF, tG, tH,
            0x28db77f523047d84L /* K72 */ + m8 /* W72 */,
            0x32caab7b40c72493L /* K73 */ + m9 /* W73 */,
            0x3c9ebe0a15c9bebcL /* K74 */ + mA /* W74 */,
            0x431d67c49c100d4cL /* K75 */ + mB /* W75 */,
            0x4cc5d4becb3e42b6L /* K76 */ + mC /* W76 */,
            0x597f299cfc657e2aL /* K77 */ + mD /* W77 */,
            0x5fcb6fab3ad6faecL /* K78 */ + mE /* W78 */,
            0x6c44198c4a475817L /* K79 */ + mF /* W79 */);
        hA += tA; hB += tB; hC += tC; hD += tD;
        hE += tE; hF += tF; hG += tG; hH += tH;
    }

    private final void computeRounds(
            long a, long b, long c, long d, long e, long f, long g, long h,
            long km0, long km1, long km2, long km3,
            long km4, long km5, long km6, long km7) {
        d += h += km0
               +  ((e >>> 14) ^ (e >>> 18) ^ (e >>> 41) ^
                   (e << 23) ^ (e << 46) ^ (e << 50)) /* Sigma1(e) */
               +  ((e & (f ^ g)) ^ g) /* Ch(e, f, g) */;
             h += ((a >>> 28) ^ (a >>> 34) ^ (a >>> 39) ^
                   (a << 25) ^ (a << 30) ^ (a << 36)) /* Sigma0(a) */
               +  ((a & b) | ((a | b) & c)) /* Maj(a, b, c) */;
        c += g += km1
               +  ((d >>> 14) ^ (d >>> 18) ^ (d >>> 41) ^
                   (d << 23) ^ (d << 46) ^ (d << 50)) /* Sigma1(d) */
               +  ((d & (e ^ f)) ^ f) /* Ch(d, e, f) */;
             g += ((h >>> 28) ^ (h >>> 34) ^ (h >>> 39) ^
                   (h << 25) ^ (h << 30) ^ (h << 36)) /* Sigma0(h) */
               +  ((h & a) | ((h | a) & b)) /* Maj(h, a, b) */;
        b += f += km2
               +  ((c >>> 14) ^ (c >>> 18) ^ (c >>> 41) ^
                   (c << 23) ^ (c << 46) ^ (c << 50)) /* Sigma1(c) */
               +  ((c & (d ^ e)) ^ e) /* Ch(c, d, e) */;
             f += ((g >>> 28) ^ (g >>> 34) ^ (g >>> 39) ^
                   (g << 25) ^ (g << 30) ^ (g << 36)) /* Sigma0(g) */
               +  ((g & h) | ((g | h) & a)) /* Maj(g, h, a) */;
        a += e += km3
               +  ((b >>> 14) ^ (b >>> 18) ^ (b >>> 41) ^
                   (b << 23) ^ (b << 46) ^ (b << 50)) /* Sigma1(b) */
               +  ((b & (c ^ d)) ^ d) /* Ch(b, c, d) */;
             e += ((f >>> 28) ^ (f >>> 34) ^ (f >>> 39) ^
                   (f << 25) ^ (f << 30) ^ (f << 36)) /* Sigma0(f) */
               +  ((f & g) | ((f | g) & h)) /* Maj(f, g, h) */;
        tH =
        h += d += km4
               +  ((a >>> 14) ^ (a >>> 18) ^ (a >>> 41) ^
                   (a << 23) ^ (a << 46) ^ (a << 50)) /* Sigma1(a) */
               +  ((a & (b ^ c)) ^ c) /* Ch(a, b, c) */;
             tD =
             d += ((e >>> 28) ^ (e >>> 34) ^ (e >>> 39) ^
                   (e << 25) ^ (e << 30) ^ (e << 36)) /* Sigma0(e) */
               +  ((e & f) | ((e | f) & g)) /* Maj(e, f, g) */;
        tG =
        g += c += km5
               +  ((h >>> 14) ^ (h >>> 18) ^ (h >>> 41) ^
                   (h << 23) ^ (h << 46) ^ (h << 50)) /* Sigma1(h) */
               +  ((h & (a ^ b)) ^ b) /* Ch(h, a, b) */;
             tC =
             c += ((d >>> 28) ^ (d >>> 34) ^ (d >>> 39) ^
                   (d << 25) ^ (d << 30) ^ (d << 36)) /* Sigma0(d) */
               +  ((d & e) | ((d | e) & f)) /* Maj(d, e, f) */;
        tF =
        f += b += km6
               +  ((g >>> 14) ^ (g >>> 18) ^ (g >>> 41) ^
                   (g << 23) ^ (g << 46) ^ (g << 50)) /* Sigma1(g) */
               +  ((g & (h ^ a)) ^ a) /* Ch(g, h, a) */;
             tB =
             b += ((c >>> 28) ^ (c >>> 34) ^ (c >>> 39) ^
                   (c << 25) ^ (c << 30) ^ (c << 36)) /* Sigma0(c) */
               +  ((c & d) | ((c | d) & e)) /* Maj(c, d, e) */;
        tE =
        e +( a += km7
               +  ((f >>> 14) ^ (f >>> 18) ^ (f >>> 41) ^
                   (f << 23) ^ (f << 46) ^ (f << 50)) /* Sigma1(f) */
               +  ((f & (g ^ h)) ^ h) /* Ch(f, g, h) */);
             tA =
             a +( ((b >>> 28) ^ (b >>> 34) ^ (b >>> 39) ^
                   (b << 25) ^ (b << 30) ^ (b << 36)) /* Sigma0(b) */
               +  ((b & c) | ((b | c) & d)) /* Maj(b, c, d) */);
    }

    private final void scheduleBlock() {
        long i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, iA, iB, iC, iD, iE, iF;

        i0 = m0 += (i9=m9) /* W09 */ +
                 (((iE=mE) >>> 6) ^ (iE >>> 19) ^ (iE >>> 61) ^
                  (iE << 3) ^ (iE << 45)) /* sigma1(W14) */ +
                 (((i1=m1) >>> 1) ^ (i1 >>> 7) ^ (i1 >>> 8) ^
                  (i1 << 56) ^ (i1 << 63)) /* sigma0(W01) */; /* W16 */
        m1 = i1 += (iA=mA) /* W10 */ +
                 (((iF=mF) >>> 6) ^ (iF >>> 19) ^ (iF >>> 61) ^
                  (iF << 3) ^ (iF << 45)) /* sigma1(W15) */ +
                 (((i2=m2) >>> 1) ^ (i2 >>> 7) ^ (i2 >>> 8) ^
                  (i2 << 56) ^ (i2 << 63)) /* sigma0(W02) */; /* W17 */
        m2 = i2 += (iB=mB) /* W11 */ +
                 ((i0 >>> 6) ^ (i0 >>> 19) ^ (i0 >>> 61) ^
                  (i0 << 3) ^ (i0 << 45)) /* sigma1(W16) */ +
                 (((i3=m3) >>> 1) ^ (i3 >>> 7) ^ (i3 >>> 8) ^
                  (i3 << 56) ^ (i3 << 63)) /* sigma0(W03) */; /* W18 */
        m3 = i3 += (iC=mC) /* W12 */ +
                 ((i1 >>> 6) ^ (i1 >>> 19) ^ (i1 >>> 61) ^
                  (i1 << 3) ^ (i1 << 45)) /* sigma1(W17) */ +
                 (((i4=m4) >>> 1) ^ (i4 >>> 7) ^ (i4 >>> 8) ^
                  (i4 << 56) ^ (i4 << 63)) /* sigma0(W04) */; /* W19 */
        m4 = i4 += (iD=mD) /* W13 */ +
                 ((i2 >>> 6) ^ (i2 >>> 19) ^ (i2 >>> 61) ^
                  (i2 << 3) ^ (i2 << 45)) /* sigma1(W18) */ +
                 (((i5=m5) >>> 1) ^ (i5 >>> 7) ^ (i5 >>> 8) ^
                  (i5 << 56) ^ (i5 << 63)) /* sigma0(W05) */; /* W20 */
        m5 = i5 += iE /* W14 */ +
                 ((i3 >>> 6) ^ (i3 >>> 19) ^ (i3 >>> 61) ^
                  (i3 << 3) ^ (i3 << 45)) /* sigma1(W19) */ +
                 (((i6=m6) >>> 1) ^ (i6 >>> 7) ^ (i6 >>> 8) ^
                  (i6 << 56) ^ (i6 << 63)) /* sigma0(W06) */; /* W21 */
        m6 = i6 += iF /* W15 */ +
                 ((i4 >>> 6) ^ (i4 >>> 19) ^ (i4 >>> 61) ^
                  (i4 << 3) ^ (i4 << 45)) /* sigma1(W20) */ +
                 (((i7=m7) >>> 1) ^ (i7 >>> 7) ^ (i7 >>> 8) ^
                  (i7 << 56) ^ (i7 << 63)) /* sigma0(W07) */; /* W22 */
        m7 = i7 += i0 /* W16 */ +
                 ((i5 >>> 6) ^ (i5 >>> 19) ^ (i5 >>> 61) ^
                  (i5 << 3) ^ (i5 << 45)) /* sigma1(W21) */ +
                 (((i8=m8) >>> 1) ^ (i8 >>> 7) ^ (i8 >>> 8) ^
                  (i8 << 56) ^ (i8 << 63)) /* sigma0(W08) */; /* W23 */
        m8 = i8 += i1 /* W17 */ +
                 ((i6 >>> 6) ^ (i6 >>> 19) ^ (i6 >>> 61) ^
                  (i6 << 3) ^ (i6 << 45)) /* sigma1(W22) */ +
                 ((i9 >>> 1) ^ (i9 >>> 7) ^ (i9 >>> 8) ^
                  (i9 << 56) ^ (i9 << 63)) /* sigma0(W09) */; /* W24 */
        m9 = i9 += i2 /* W18 */ +
                 ((i7 >>> 6) ^ (i7 >>> 19) ^ (i7 >>> 61) ^
                  (i7 << 3) ^ (i7 << 45)) /* sigma1(W23) */ +
                 ((iA >>> 1) ^ (iA >>> 7) ^ (iA >>> 8) ^
                  (iA << 56) ^ (iA << 63)) /* sigma0(W10) */; /* W25 */
        mA = iA += i3 /* W19 */ +
                 ((i8 >>> 6) ^ (i8 >>> 19) ^ (i8 >>> 61) ^
                  (i8 << 3) ^ (i8 << 45)) /* sigma1(W24) */ +
                 ((iB >>> 1) ^ (iB >>> 7) ^ (iB >>> 8) ^
                  (iB << 56) ^ (iB << 63)) /* sigma0(W11) */; /* W26 */
        mB = iB += i4 /* W20 */ +
                 ((i9 >>> 6) ^ (i9 >>> 19) ^ (i9 >>> 61) ^
                  (i9 << 3) ^ (i9 << 45)) /* sigma1(W25) */ +
                 ((iC >>> 1) ^ (iC >>> 7) ^ (iC >>> 8) ^
                  (iC << 56) ^ (iC << 63)) /* sigma0(W12) */; /* W27 */
        mC = iC += i5 /* W21 */ +
                 ((iA >>> 6) ^ (iA >>> 19) ^ (iA >>> 61) ^
                  (iA << 3) ^ (iA << 45)) /* sigma1(W26) */ +
                 ((iD >>> 1) ^ (iD >>> 7) ^ (iD >>> 8) ^
                  (iD << 56) ^ (iD << 63)) /* sigma0(W13) */; /* W28 */
        mD = iD += i6 /* W22 */ +
                 ((iB >>> 6) ^ (iB >>> 19) ^ (iB >>> 61) ^
                  (iB << 3) ^ (iB << 45)) /* sigma1(W27) */ +
                 ((iE >>> 1) ^ (iE >>> 7) ^ (iE >>> 8) ^
                  (iE << 56) ^ (iE << 63)) /* sigma0(W14) */; /* W29 */
        mE = iE +  i7 /* W23 */ +
                 ((iC >>> 6) ^ (iC >>> 19) ^ (iC >>> 61) ^
                  (iC << 3) ^ (iC << 45)) /* sigma1(W28) */ +
                 ((iF >>> 1) ^ (iF >>> 7) ^ (iF >>> 8) ^
                  (iF << 56) ^ (iF << 63)) /* sigma0(W15) */; /* W30 */
        mF = iF +  i8 /* W24 */ +
                 ((iD >>> 6) ^ (iD >>> 19) ^ ( iD >>> 61) ^
                  (iD << 3) ^ (iD << 45)) /* sigma1(W29) */ +
                 ((i0 >>> 1) ^ (i0 >>> 7) ^ (i0 >>> 8) ^
                  (i0 << 56) ^ (i0 << 63)) /* sigma0(W16) */; /* W31 */
    }
    public static void main(String args[]){
    	long a = 0x0100L;
    	System.out.println(a);
    	a = a << 1;
    	System.out.println(a);
    	a = a >>> 3;
    	System.out.println(a);
    	
    	
    }	
}	
