LIS2DE12 interrupt çalışması

LISD2E12_INT1_THS 0x32 registerine nasıl değer verilir?
Biz LIS2DE12_CTRL_REG4 0x23 registerinde 0x16 değerini seçmişiz. bu yüzden 0x32 registerinde verilen tabloda
186mg denen g değeri ile çalışacağız. 
Ben igile registere ne yazarsam yazayım o değer g değeri ile çarpılıp 1000 sayısına bölünerek değeri bulacağız.
Burada LISD2E12_INT1_THS registerine 0x14 yani decimal olarak 20 yazıp 186x20 yapıyoruz.
Bu da yaklaşık olarak 3.7g edecektir. Başka değerler de denenip testler edilebilir.
Accelometeyi biraz kuvvetli sallayınca ledin interrupt vesilesiyle yanmasını hedefliyoruz.




