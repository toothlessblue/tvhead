class RenderItem {
    public:
        int zIndex = 0;

        RenderItem();

        virtual void tick();

        virtual void render();
};
