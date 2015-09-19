package nkdhny.runtag;

/**
 * Created by nkdhny on 19.09.15.
 */
public class Tag {

    private final long id;
    private final float x;
    private final float y;


    public Tag(long id, float x, float y) {
        this.id = id;
        this.x = x;
        this.y = y;
    }


    public long getId() {
        return id;
    }

    public float getX() {
        return x;
    }

    public float getY() {
        return y;
    }


    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Tag tag = (Tag) o;

        if (id != tag.id) return false;
        if (Float.compare(tag.x, x) != 0) return false;
        return Float.compare(tag.y, y) == 0;

    }

    @Override
    public int hashCode() {
        int result = (int) (id ^ (id >>> 32));
        result = 31 * result + (x != +0.0f ? Float.floatToIntBits(x) : 0);
        result = 31 * result + (y != +0.0f ? Float.floatToIntBits(y) : 0);
        return result;
    }


    @Override
    public String toString() {
        return "Tag{" +
                "id=" + id +
                ", x=" + x +
                ", y=" + y +
                '}';
    }
}
