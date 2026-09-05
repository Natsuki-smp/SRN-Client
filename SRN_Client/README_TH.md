# SRN Client — Bedrock 1.26.45.1

โครงโปรเจกต์สำหรับ Client DLL ของ Minecraft Bedrock Windows/GDK ตามสเปกที่ขอ:

- C = FOV 30 → 60 → 90
- X = Render Distance 6 → 8 → 10
- G = FullBright ON/OFF
- Z = reserved for EchoST/Stronghold measurement integration
- เน้น polling ต่ำและไม่ทำงานหนักทุก frame

## สำคัญ
ไฟล์นี้เป็น **source project** ไม่ใช่ DLL ที่พร้อมใช้งานกับ Minecraft 1.26.45.1 ทันที
เพราะ DLL จริงต้องมี hook/offset/symbol ที่ตรงกับ build ของ Minecraft Windows GDK 1.26.45.1
การเดา offset อาจทำให้เกม crash ได้ จึงไม่ได้ใส่ offset ปลอม

## Build
ต้อง build เป็น Windows x64 DLL ด้วย Visual Studio + Windows SDK หรือ toolchain ที่เข้ากันได้

```powershell
cmake -S . -B build -A x64
cmake --build build --config Release
```

ผลลัพธ์โดยทั่วไป:
`build/Release/SRN_Client.dll`

## BedrockOnLinux
เมื่อมี DLL ที่ build และ hook กับ 1.26.45.1 เรียบร้อยแล้ว ให้ใช้:
Settings → Tools → Inject a client DLL…

อย่าเปิด Auto-inject จนกว่าจะทดสอบ manual injection สำเร็จ
