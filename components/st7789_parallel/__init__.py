import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import display
from esphome.const import CONF_ID

DEPENDENCIES = ["display"]

st7789_ns = cg.esphome_ns.namespace("st7789_parallel")
ST7789ParallelDisplay = st7789_ns.class_("ST7789ParallelDisplay", display.DisplayBuffer)

CONFIG_SCHEMA = display.FULL_DISPLAY_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(ST7789ParallelDisplay),
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await display.register_display(var, config)
