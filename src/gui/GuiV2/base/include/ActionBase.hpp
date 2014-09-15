
#ifndef HPP_ACTIONBASE
#define HPP_ACTIONBASE

#include "AResource.hpp"
#include "Manager.hpp"

class ActionBase : public AResource
{
    public:
    static char const* const manager_id;

    enum ActionType
    {
        VariableAssign,     // var = to_var
        PlayerMove,         // 
        PlayerSetImage,     //
        PositionSetImage,   // PositionMgr.set_image(x, y, ImageId, x_img, y_img)
        TextOn,             // TextMgr.activate_text(TextId)
        TextOff,            // TextMgr.deactivate_text(TextId)
        EventQueue,         // EventMgr.queue(EventId)
        SoundOn,            // SoundMgr.activate_sound(SoundId)
        SoundOff,           // SoundMgr.deactivate_sound(SoundId)
        ActionTypeTotal,
    };

    enum ActionFlag
    {
        NextIsBranch=(1<<0),
    };

    typedef struct
    {
        int id_next;    // next branch or action
        int flags;      // next_is_branch, ...
        ActionType type;
        union
        {
            int id_target;      // text, event, sound or ... ?
            struct              // if id_target is Variable (implying type is VariableAssign), Variable(id_target).set_value(Variable(id_from_var).value())
            {
                int id_var_to;
                int id_var_from;    
            } variable_assign;
            struct              // PlayerMove
            {
                int id_x;
                int id_y;
            } player_move;
            struct {
                int id_image;
                int image_tile_at_x;
                int image_tile_at_y;
            } player_image;
            struct {
                int x;
                int y;
                int id_image;
                int image_tile_at_x;
                int image_tile_at_y;
            } position_image;
            struct
            {
                int id_event;
                int delay;
            } event_queue;
        };
    } ResourceData;
    
    ResourceData res_data;

    protected:
    virtual unsigned int _res_data_size() const;
    virtual void const* _res_data() const;
    virtual void* _res_data();
};

#endif

