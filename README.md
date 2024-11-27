# ĐỒ HỌA MÁY TÍNH (COMPUTER GRAPHICS)
## Tổng quan
- Dưới đây là danh sách các bài tập về đồ họa máy tính.

| STT | Nội dung |
|--------------|-------|
| 0 | Mở đầu, làm quen với OpenGL |
| 1 | Vẽ đường thẳng (4 trường hợp hệ số góc), đường tròn, đường elip (Thuật toán Bressenham, Midpoint) và các đường cong khác (Parabol, Hyperbol, Sin(x), Cos(x)) |
| 2 | Thuật toán xén hình (Cohen-Sutherland, Chia nhị phân) và thuật toán tô màu (Theo đường biên (đệ quy/không đệ quy), Theo dòng quét) |
| 3 | Các phép biến đổi 2D (Tịnh tiến, Tỉ lệ với tâm tỉ lệ (x0, y0), Quay với tâm quay (x0, y0), Đối xứng qua đường thẳng y = ax + b) |
| 4 | Các phép biến đổi 3D (Tịnh tiến, Đối xứng qua mặt phẳng xOy, yOz, xOz, Tỉ lệ với tâm tỉ lệ (x0, y0, z0), Quay quanh các trục tọa độ) và biểu diễn vật thể theo 2 mô hình (Khung kết nối, Mặt đa giác) |
| 5 | Vẽ các mặt có quy tắc (Mặt trụ, Mặt nón), mặt tròn xoay (Mặt cầu, Ellipsoid, Hypeboloid, Torus), đường cong và mặt cong Bezier |
| 6 | Thuật toán khử đường, mặt khuất (Thuật toán khử mặt sau Back-face, Depth-Sorting/Painter, Depth-buffer/Z-buffer) |
| 7 | Thuật toán tô bóng (Tô bóng hằng Lambert, Tô bóng nội suy Gouraud, Tô bóng nội suy Phong) |
## Các công nghệ được sử dụng
- Ngôn ngữ: C/C++.
- Thư viện: OpenGL.
## Cách cài đặt
- Tải và cài đặt Dev-C++, thư viện OpenGL.
- Mở file project và chèn thư viện vào project.
- Biên dịch và chạy file.
- Trong trường hợp muốn chạy file khác trong cùng 1 project:
  <ul>
  <li>Chuột phải vào project -> Chọn Project Options</li>
  <li>Ở tab Files, tick 2 ô đầu tiên đối với file cần thực thi, và ngược lại với các file còn lại</li>
  <li>Ấn OK để kết thúc</li>
  </ul>
## Tác giả
* Hứa Viết Thái ([hvt299](https://github.com/hvt299)).
