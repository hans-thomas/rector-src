<?php

namespace Rector\Tests\DeadCode\Rector\ClassMethod\RemoveUselessOverrideAttributeRector\Fixture;

class ExtendsAbstractWithExtendsParentClass {
    public function foo(): void
    {
        echo 'self::foo';
    }
}
abstract class ExtendsAbstractWithExtendsContract extends ExtendsAbstractWithExtendsParentClass {}

final class ExtendsAbstractWithExtendsClass extends ExtendsAbstractWithExtendsContract
{
    #[\Override]
    public function foo(): void
    {
        echo 'foo';
    }

    #[\Override]
    public function bar(): void
    {
        echo 'bar';
    }
}
?>
-----
<?php

namespace Rector\Tests\DeadCode\Rector\ClassMethod\RemoveUselessOverrideAttributeRector\Fixture;

class ExtendsAbstractWithExtendsParentClass {
    public function foo(): void
    {
        echo 'self::foo';
    }
}
abstract class ExtendsAbstractWithExtendsContract extends ExtendsAbstractWithExtendsParentClass {}

final class ExtendsAbstractWithExtendsClass extends ExtendsAbstractWithExtendsContract
{
    #[\Override]
    public function foo(): void
    {
        echo 'foo';
    }

    public function bar(): void
    {
        echo 'bar';
    }
}
?>
