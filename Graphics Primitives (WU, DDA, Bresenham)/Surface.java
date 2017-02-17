import java.awt.*;
import javax.swing.JPanel;
import java.lang.Math;

class Surface extends JPanel {

    public final int SIZE_OF_PIXEL = 5;


    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        DDA(g, 3, 3, 40, 8, Color.DARK_GRAY );
        Bresenham(g, 3, 10, 60, 37, Color.DARK_GRAY );
        WU(g, 3, 50, 46, 45);
        Bresenham_Cir(100, 25, 20, g);
    }


    private void drawPoint(Graphics g, float x, float y) {
        Graphics2D g2 = (Graphics2D) g;

        g2.fillRect(Math.round(x) * SIZE_OF_PIXEL, Math.round(y) * SIZE_OF_PIXEL, SIZE_OF_PIXEL, SIZE_OF_PIXEL);
    }


    private void DDA(Graphics g, float x1, float y1, float x2, float y2, Color c) {
        g.setColor(c);

        if ((x1 == x2) && (y1 == y2)) {
            drawPoint(g, x1, y1);
        }
        else {
            float dX, dY;
            int xstart = Math.round(x1);
            int ystart = Math.round(y1);
            int xend = Math.round(x2);
            int yend = Math.round(y2);
            int len = Math.max(Math.abs(xend - xstart), Math.abs(yend - ystart));
            dX = (x2 - x1) / len;
            dY = (y2 - y1) / len;
            drawPoint(g, x1, y1);
            for (int i = 0; i < len; i++) {
                drawPoint(g, x1 += dX, y1 += dY);
            }
        }
    }


    private void Bresenham(Graphics g, int x1, int y1, int x2, int y2, Color c){
        g.setColor(c);

        if ((x1 == x2) && (y1 == y2)) {
            drawPoint(g, x1, y1);

        } else {
            float dX = Math.abs(x2 - x1);
            float dY = Math.abs(y2 - y1);
            float err = dX - dY;

            int posun_x, posun_y;

            posun_x = (x1 < x2) ? 1 : -1;
            posun_y = (y1 < y2) ? 1 : -1;

            while ((x1 != x2) || (y1 != y2)) {

                float p = 2 * err;

                if (p > -dY) {
                    err = err - dY;
                    x1 = x1 + posun_x;
                }
                if (p < dX) {
                    err = err + dX;
                    y1 = y1 + posun_y;
                }
                drawPoint(g, x1, y1);
            }
        }
    }


    private void WU(Graphics g, int x1, int y1, int x2, int y2) {
        if (x2 < x1) {
            x1 += x2;
            x2 = x1 - x2;
            x1 -= x2;
            y1 += y2;
            y2 = y1 - y2;
            y1 -= y2;
        }
        int dx = x2 - x1;
        int dy = y2 - y1;
    
        if (dx == 0) {
            g.setColor(Color.BLACK);
            for (int i = 0 ; i < SIZE_OF_PIXEL; i++ )
                g.drawLine(x1 * SIZE_OF_PIXEL + i, y1 * SIZE_OF_PIXEL, x2 * SIZE_OF_PIXEL + i, y2 * SIZE_OF_PIXEL);
            return;
        }
        if (dy == 0) {
            g.setColor(Color.BLACK);
            for (int i = 0 ; i < SIZE_OF_PIXEL; i++ )
                g.drawLine(x1 * SIZE_OF_PIXEL, y1 * SIZE_OF_PIXEL + i, x2 * SIZE_OF_PIXEL, y2 * SIZE_OF_PIXEL + i);
            return;
        }

        float err;
        g.setColor(Color.BLACK);
        drawPoint(g, x1, y1);
        if (Math.abs(dx) > Math.abs(dy)) {
            err = (float) dy / dx;
            float intery = y1 + err;
            for (int x = x1 + 1; x < x2; ++x) {
                g.setColor(new Color(0, 0, 0, (int) (255 - fractionalPart(intery) * 255))); 
                drawPoint(g, x, (int) intery);
                g.setColor(new Color(0, 0, 0, (int) (fractionalPart(intery) * 255)));
                drawPoint(g, x, (int) intery + 1);
                intery += err;
            }
        } else {
            err = (float) dx / dy;
            float interx = x1 + err;
            for (int y = y1 + 1; y < y2; ++y) {
                g.setColor(new Color(0, 0, 0, (int) (255 - fractionalPart(interx) * 255)));
                drawPoint(g, (int) interx, y);
                g.setColor(new Color(0, 0, 0, (int) (fractionalPart(interx) * 255)));
                drawPoint(g, (int) interx + 1, y);
                interx += err;
            }
        }
        g.setColor(Color.BLACK);
        drawPoint(g, x2, y2);

    }

        private float fractionalPart(float x) {
            int tmp = (int) x;
            return x - tmp;
        }



    private void Bresenham_Cir(int center_x, int center_y, int R, Graphics g){
        int x = 0, y = R, sigma, delta = 1 - 2 * R;
        while (y >= 0){
            drawPoint(g, center_x + x, center_y - y);     // 1 четверть
            drawPoint(g, center_x - x, center_y - y);     // 2 четверть
            drawPoint(g, center_x - x, center_y + y);     // 3 четверть
            drawPoint(g, center_x + x, center_y + y);     // 4 четверть
            sigma = 2 * (delta + y) - 1;
            if (delta < 0 && sigma <= 0) {          //перемещение по горизонтали
                x++;
                delta += 2 * x + 1;
                continue;
            }
            sigma = 2 * (delta - x) - 1;
            if (delta > 0 && sigma > 0) {            //перемещение по вертикали
                y--;
                delta += 1 - 2 * y;
                continue;
            }
                                                     //перемещение по диагонали
                x++;
                delta += 2 * (x - y);
                y--;
        }
    }


}

