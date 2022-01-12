const N = 1000000000;

function qsort(A, l, n) // l se koristi za početak segmenta tj. pomak koji treba koristiti za svaku referencu na polje u ovoj razini (JS ne podržava pokazivače)
{
    if (n <= 1) {
        return;
    }

    //let i = Math.floor(Math.random() * n);
    let i = 0;
    [A[i + l], A[l]] = [A[l], A[i + l]]; // zamjena i-tog i nultog elementa polja

    let j = n;
    let k = 0;

    while (1) { // Hoareova particijska shema; kada pomaknemo pokazivač, ne stajemo s pomicanjem dok je element isti ili dok se pokazivači ne sudare
        do k++; while (k < n && A[k + l] < A[l]);
        do j--; while (A[j + l] > A[l]);
        if (j < k) break;
        [A[j + l], A[k + l]] = [A[k + l], A[j + l]]; // zamjena j-tog i k-tog elementa polja
    }

    [A[j + l], A[l]] = [A[l], A[j + l]]; // konačna zamjena
    qsort(A, l, j);
    qsort(A, l + j + 1, n - j - 1);
}

function med3(a, b, c) // odabir medijana od dana 3 elementa
{
    if (a < b) {
        if (b < c) {
            return b;
        } else if (a < c) {
            return c;
        } else {
            return a;
        }
    } else {
        if (b > c) {
            return b;
        } else if (c > a) {
            return a;
        } else {
            return c;
        }
    }
}

function qsort_med3(A, l, n)
{
    if (n <= 1) {
        return;
    }

    let i1 = Math.floor(Math.random() * n);
    let i2 = Math.floor(Math.random() * n);
    let i3 = Math.floor(Math.random() * n);
    let med = med3(i1, i2, i3);

    [A[med + l], A[l]] = [A[l], A[med + l]];

    let j = n;
    let k = 0;

    while (1) { // Hoareova particijska shema; kada pomaknemo pokazivač, ne stajemo s pomicanjem dok je element isti ili dok se pokazivači ne sudare
        do k++; while (k < n && A[k + l] < A[0]);
        do j--; while (A[j + l] > A[l]);
        if (j < k) break;
        [A[j + l], A[k + l]] = [A[k + l], A[j + l]]; // zamjena j-tog i k-tog elementa polja
    }

    [A[j + l], A[l]] = [A[l], A[j + l]]; // konačna zamjena
    qsort_med3(A, l, j);
    qsort_med3(A, l + j + 1, n - j - 1);
}

function randgen(n = N) // generira polje od n nasumičnih realnih brojeva
{
    let A = [];
    for (let i = 0; i < n; ++i) {
        A.push(Math.random() * N);
    }

    return A;
}