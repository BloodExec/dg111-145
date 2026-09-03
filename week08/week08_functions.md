# Week 8 — Functions Reference

**Function Reference — `ex02_game_utils.c`**

| Function                                    | ทำหน้าที่                                                 | Returns                      |
| ------------------------------------------- | ------------------------------------------------------------------ | ---------------------------- |
| `int clamp(int value, int min, int max)`  | จำกัดค่า value ให้อยู่ระหว่าง min และ max | ค่าที่ clamp แล้ว  |
| `float lerp(float a, float b, float t)`   | Linear interpolation ระหว่าง a และ b ตาม t            | ค่าที่คำนวณได้ |
| `int randomRange(int min, int max)`       | สุ่มตัวเลขระหว่าง min และ max                  | ค่าสุ่ม               |
| `float percentOf(int current, int total)` | คำนวณเปอร์เซ็นต์                                   | ค่าเปอร์เซ็นต์ |

## คำถาม Reflection — Exercise 2

### 2.1 `clamp` — Pass by Value

**คำถาม:** ทำไม `hp` ใน `main()` ถึงยังเป็น 150 ทั้งที่ `value` ใน `clamp()` ถูกเขียนทับเป็น 100 ไปแล้ว?

**คำตอบ: เพราะเป็น Pass by Value ทำให้ `value` เป็นสำเนาของ `hp` การแก้ `value` จึงไม่กระทบ `hp`**

### 2.2 `lerp` — Local Scope

**คำถาม:** ทำไม `main()` ถึงมองไม่เห็นตัวแปร `result` ทั้งที่มันถูกประกาศไว้ในไฟล์เดียวกัน?

**คำตอบ: เพราะตัวแปร result ถูกประกาศในฟังก์ชัน lerp ซึ่งเป็น local scope ทำให้ main() ไม่สามารถมองเห็นหรือใช้งานได้แม้ประกาศไว้ในไฟล์เดียวกัน**

### 2.3 `randomRange` — Pass by Value

**คำถาม:** ทำไม `diceMin` ใน `main()` ถึงยังเป็น 1 ทั้งที่ `min` ใน `randomRange()` ถูกบวกเพิ่มเป็น 101 ไปแล้ว?

**คำตอบ: เพราะ min ใน randomRange() ส่งค่าแบบ Pass by Value ทำให้ min เป็นแค่สำเนาของ diceMin ดังนั้นเมื่อแก้ค่า min เป็น 101 ก็จะเปลี่ยนเฉพาะฟังก์ชัน randomRange() ไม่ได้เปลี่ยน diceMin ใน main()**

### 2.4 `percentOf` — Pass by Value

**คำถาม:** ทำไม `score` ใน `main()` ถึงไม่เปลี่ยนเป็น 0 ตาม `current` ทั้งที่ `percentOf()` แก้ `current = 0;` ไปแล้ว?

**คำตอบ :เพราะ current ใน percentOf() ส่งค่าแบบ Pass by Value ทำให้ current เป็นแค่สำเนาของ score ดังนั้นเมื่อแก้ค่า current เป็น 0 ก็จะเปลี่ยนเฉพาะฟังก์ชัน percentOf() ไม่ได้เปลี่ยน score ใน main()**
